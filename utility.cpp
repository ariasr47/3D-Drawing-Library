//
//  utility.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#define GL_SILENCE_DEPRECATION
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>

#include <glm/glm.hpp>

#include "global.hpp"
#include "polyhedron.hpp"
#include "utility.hpp"
#include "translate.h"

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(window_width, window_height);

	glutCreateWindow("drawinglib");

	glClearColor(1, 1, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(-1, -1);

	loadData();
}

void loadData() {
	if (std::ifstream data(filename); data.is_open())
		for (auto i = 0, num_objects = data.get() - '0'; i < num_objects; i++) {
			db.object_table.emplace(i, new Geometry::Polyhedron(i, data));
		}
	else
		std::cout << strerror(errno) << std::endl;
}

void render() {
	memset(pixel_buffer, 255, buffer_size); // clear pixel buffer

	for (auto& [key, obj] : db.object_table)
		obj->draw();

	glDrawPixels(buffer_width, buffer_height, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);

	glFlush();
}

void user_interface()
{
	static auto flag = true;
	
	char input;

	if (flag) {
		std::cout << "Choose Line Drawing Algorithm:" << std::endl;
		std::cout << "\t1. DDA Algorithm" << std::endl;
		std::cout << "\t2. Bresenham Algorithm" << std::endl;
		std::cin >> input;
		line_alg = LineAlg(input);

		std::cout << "Choose Shading Method:" << std::endl;
		std::cout << "\t1. Flat Shading" << std::endl;
		std::cout << "\t2. Gouraud Shading" << std::endl;
		std::cout << "\t3. Phong Lighting Model" << std::endl;
		std::cin >> input;
		shading_alg = ShadingAlg(input);

		std::cout << "Choose Visibility Algorithm:" << std::endl;
		std::cout << "\t1. Painter's Algorithm" << std::endl;
		std::cout << "\t2. Back Face Culling" << std::endl;
		std::cin >> input;
		vis_alg = VisibilityAlg(input);
		flag = false;
	} else {
		int obj_id;
		std::cout << "Choose object:" << std::endl;
		for (auto &[key, obj] : db.object_data)
			std::cout << "id " << key << std::endl;
		std::cin >> obj_id;
		std::cout << "Choose option:" << std::endl;
		std::cout << "\t1. Scale" << std::endl;
		std::cout << "\t2. Translate" << std::endl;
		std::cout << "\t3. Rotate" << std::endl;
		std::cin >> input;

		switch(input)
		{
		case '1':
			break;
		case '2':
			float tx, ty, tz;
			std::cin >> tx >> ty >> tz;
			translate(obj_id, tx, ty, tz);
			break;
		case '3':
			break;
		}
	}

	render(); 

	glutPostRedisplay();
}


bool is_consecutive(int x, int y)
{
	return (y == x - 1) || (y == x + 1);
}

/*
std::pair<int, int> get_inner_bounds(int y, edge_t e1, edge_t e2) {
	auto pos1 = e1->get_intersection(y),
		pos2 = e2->get_intersection(y);

	auto left = round(*(pos1.begin())),
		right = round(*(pos2.begin()));

	if (left < right) {
		left = round(*(pos1.rbegin()));
	} else if (left > right) {
		right = left;
		left = round(*(pos2.rbegin()));
	}

	return std::make_pair(left, right);
}

void get_outer_bounds(int y, edge_t e1, edge_t e2) {
}

std::pair<glm::vec3, glm::vec3> Interpolate(int y, outer_bound left, outer_bound right) {
	auto eL = left.second,
		eR = right.second;

	glm::vec3 I1 = vertex_list[eL->v1]->I,
		I2 = vertex_list[eL->v2]->I;

	float y1 = eL->ymin,
		y2 = eL->ymax;

	int dy = y2 - y1;

	float scale1 = (y - y1) / dy,
		scale2 = (y2 - y) / dy;

	glm::vec3 IL = I2 * scale1 + I1 * scale2;

	I1 = vertex_list[eR->v1]->I;
	I2 = vertex_list[eR->v2]->I;

	y1 = eR->ymin;
	y2 = eR->ymax;

	dy = y2 - y1;

	scale1 = (y - y1) / dy;
	scale2 = (y2 - y) / dy;

	glm::vec3 IR = I1 * scale1 + I2 * scale2;

	return std::make_pair(IL, IR);
}

glm::vec3 Interpolate(float x, float x1, float x2, glm::vec3 IL, glm::vec3 IR) {
	if (x == x1) {
		return IL;
	}
	else if (x == x2) {
		return IR;
	}

	int dx = x2 - x1;

	float scale1 = (x2 - x) / dx,
		scale2 = (x - x1) / dx;

	return IL * scale1 + IR * scale2;
}

glm::vec3 ComputeIntensity(Geometry::Vertex P) {
	float max = -999999.00;

	glm::vec3 i_diff, i_spec, l, v, r, i;
	glm::vec3 p(P.pos.x, P.pos.y, P.pos.z);

	p /= sqrt(pow(p[0], 2) + pow(p[1], 2) + pow(p[2], 2));
	x /= sqrt(pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2));
	f /= sqrt(pow(f[0], 2) + pow(f[1], 2) + pow(f[2], 2));

	l = x - p;
	v = f - p;
	r = 2 * dot(P.n, l) * P.n - l;

	r /= sqrt(pow(r[0], 2) + pow(r[1], 2) + pow(r[2], 2));
	l /= sqrt(pow(l[0], 2) + pow(l[1], 2) + pow(l[2], 2));
	v /= sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));

	if (dot(P.n, l) > 0)
		i_diff = ka * Ia + (kd * Il) * dot(P.n, l);
	else if (dot(P.n, l) <= 0)
		i_diff = ka * Ia;
	if (dot(v, r) > 0 && dot(P.n, l) > 0)
		i_spec = (ks * Il) * float(pow(dot(v, r), 2));
	else if (dot(v, r) <= 0 || dot(P.n, l) <= 0)
		i_spec = { 0.0f,0.0f,0.0f };

	i = i_diff + i_spec;

	for (int z = 0; z < 3; z++)
		if (i[z] > max)
			max = i[z];

	i /= max;

	return i;
}
*/