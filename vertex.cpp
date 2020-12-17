//
//  vertex.cpp
//  3D_Drawing_System
//
//  Created by Rodrigo on 10/31/19.
//

#include "global.hpp"

#include "vertex.hpp"

using namespace Geometry;

Vertex::Vertex(int id, std::ifstream& data, glm::vec3 clr) : Object(id), I(clr)
{
	data >> pos.x >> pos.y >> pos.z;
}

Vertex::Vertex(const Vertex& v)
{
	n = v.n;
	I = v.I;
	pos = v.pos;
}

Vertex::Vertex(double posx, double posy, double posz)
	: pos(posx, posy, posz)
{
}

bool Vertex::operator==(const Vertex& v)
{
	return pos == v.pos;
}

glm::vec3 Vertex::operator-(const Vertex& v)
{
	return pos - v.pos;
}

std::ostream& operator << (std::ostream& out, const vertex_t v)
{
	out << "(" << v->pos.x << "," << v->pos.y << "," << v->pos.z << ")";
	return out;
}