//
//  edge.cpp
//  drawinglib
//
//  Created by Rodrigo on 10/31/19.
//

#include <algorithm>
#include <cmath>

#include "global.hpp"
#include "vertex.hpp"
#include "line.hpp"

#include "edge.hpp"

using namespace Geometry;

Edge::Edge()
{
}

Edge::Edge(int id, int id1, int id2) : Object(id), v1(id1), v2(id2)
{
	update();
}

Edge::Edge(const Edge& e)
{
	v1 = e.v1;
	v2 = e.v2;

	xmin = e.xmin;
	xmax = e.xmax;

	ymin = e.ymin;
	ymax = e.ymax;

	zmin = e.zmin;
	zmax = e.zmax;

	dx = e.dx;
	dy = e.dy;

	step = e.step;
	xstep = e.xstep;
	ystep = e.ystep;
}

void Edge::update()
{
	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	auto P1 = object_data->vertex_list[v1]->pos,
		 P2 = object_data->vertex_list[v2]->pos;

	if (P1.y > P2.y) {
		std::swap(P1, P2);
		std::swap(v1, v2);
	}

	auto x1 = round(P1.x),
		 x2 = round(P2.x);

	auto y1 = round(P1.y),
		 y2 = round(P2.y);

	auto z1 = round(P1.z),
		 z2 = round(P2.z);

	ymin = y1;
	ymax = y2;

	xmin = std::min(x1, x2);
	xmax = std::max(x1, x2);

	zmin = std::min(z1, z2);
	zmax = std::max(z1, z2);

	dx = x2 - x1;
	dy = y2 - y1;

	step = abs(dy) > abs(dx) ? abs(dy) : abs(dx);

	xstep = (double)dx / step;
	ystep = (double)dy / step;
}

void Edge::draw() {
	return;
}

std::ostream& operator << (std::ostream& out, edge_t e) {
	/*
	auto object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	out << object_data->vertex_list[e->v1] << " ---> " << object_data->vertex_list[e->v2];
	*/
	return out;
}

bool Edge::operator==(const Edge& e)
{
	return false;
}

std::pair <vertex_t, vertex_t> Edge::get_vertices()
{
	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	auto P1 = object_data->vertex_list[v1],
		 P2 = object_data->vertex_list[v2];

	return std::make_pair(P1, P2);
}
