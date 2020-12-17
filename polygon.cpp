//
//  polygon.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "global.hpp"

#include "shading.hpp"

#include "polygon.hpp"

#include "line.hpp"

using namespace Geometry;

Polygon::Polygon(int id, std::ifstream& data) : Object(id)
{
	{
		if (auto c = data.get(); c != '\n')
			data.putback(c);

		std::string line;
		std::getline(data, line);
		std::istringstream is(line);
		std::copy(std::istream_iterator<int>(is), std::istream_iterator<int>(),
			std::back_inserter(ids));
	}

	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	ids.push_back(ids[0]);

	for (unsigned j = 0; j < ids.size() - 1; j++)
	{
		auto pair = (ids[j] < ids[j + 1]) ? std::make_pair(ids[j], ids[j + 1]) : std::make_pair(ids[j + 1], ids[j]);
		if (object_data->edge_table.find(pair) == object_data->edge_table.end())
		{
			object_data->edge_table[pair] = std::make_shared<Edge>(obj_id, pair.first, pair.second);
		}
	}

	ids.pop_back();
}

Polygon::Polygon(const Polygon& p)
{
	num_edges = p.num_edges;
	num_vertices = p.num_vertices;

	xmin = p.xmin;
	xmax = p.xmax;

	ymin = p.ymin;
	ymax = p.ymax;

	zmin = p.zmin;
	zmax = p.zmax;

	N = p.N;

	D = p.D;
}

void Polygon::dump()
{
	std::cout << "\t"
		<< "Xmin: " << xmin << std::endl;
	std::cout << "\t"
		<< "Xmax: " << xmax << std::endl;

	std::cout << "\t"
		<< "Ymin: " << ymin << std::endl;
	std::cout << "\t"
		<< "Ymax: " << ymax << std::endl;

	std::cout << "\t"
		<< "Zmin: " << zmin << std::endl;
	std::cout << "\t"
		<< "Zmax: " << zmax << std::endl;

	std::cout << "\t"
		<< "Plane: " << N.x << "x + " << N.y << "y + " << N.z << "z + " << D << std::endl;
}

void Polygon::update()
{
	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	auto edges = object_data->edge_table;

	xmin = ymin = zmin = std::numeric_limits<int>::max();
	xmax = ymax = zmax = std::numeric_limits<int>::min();

	for (auto& [key,e] : edges)
	{
		xmin = std::min(xmin, e->xmin);
		xmax = std::max(xmin, e->xmax);

		ymin = std::min(ymin, e->ymin);
		ymax = std::max(ymin, e->ymax);

		zmin = std::min(zmin, e->zmin);
		zmax = std::max(zmin, e->zmax);
	}

	auto v0 = ids[0], v1 = ids[1], v2 = ids[2];

	auto PQ = *object_data->vertex_list[v1] - *object_data->vertex_list[v0],
		PR = *object_data->vertex_list[v2] - *object_data->vertex_list[v0];

	N = cross(PQ, PR);

	D = -(N.x * object_data->vertex_list[0]->pos.x + N.y * object_data->vertex_list[0]->pos.y + N.z * object_data->vertex_list[0]->pos.z);
}

void Polygon::draw()
{
	switch(shading_alg)
	{
		case ShadingAlg::FlatShading:
			flat_shading(this);
			break;
		case ShadingAlg::GouradShading:
			gouraud_shading(this);
			break;
		case ShadingAlg::PhongLightingModel:
			phong_lighting(this);
			break;
		default:
			break;
	}
}

std::vector<vertex_t> Polygon::get_vertices()
{
	std::vector<vertex_t> vertices;
	auto object_data = static_cast<polygon_data*>(db.object_data[obj_id].get());
	for (auto id : ids)
		vertices.push_back(object_data->vertex_list[id]);
	return vertices;
}

