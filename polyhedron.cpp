//
//  polyhedron.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#include <string>
#include <fstream>

#include "global.hpp"
#include "paintersAlg.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include "polygon.hpp"
#include "polyhedron.hpp"

#include "color.hpp"

using namespace Geometry;

Polyhedron::Polyhedron(int id, std::ifstream& data) : Object(id)
{
	int num_vertices, num_faces;

	db.object_data.emplace(obj_id, new polyhedron_data);
	auto *temp = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	auto clr = std::vector<glm::vec3>{ White, Green, Blue, White };
	
	data >> num_vertices;
	for (auto i = 0; i < num_vertices; i++)
		temp->vertex_list.emplace_back(new Vertex(obj_id, data, clr[i]));
	
	data >> num_faces;
	for (auto i = 0; i < num_faces; i++)
		temp->polygon_list.emplace_back(new Polygon(obj_id, data));

	update();
}

Polyhedron::Polyhedron(Polyhedron& p)
{
	obj_id = p.obj_id;
}

void Polyhedron::update()
{
	auto *temp = static_cast<polyhedron_data*>(db.object_data[obj_id].get());
	
	for (auto& [key,e] : temp->edge_table)
		e->update();

	for (auto& p : temp->polygon_list)
		p->update();
}

void Polyhedron::draw()
{
	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	switch (vis_alg) {
		case VisibilityAlg::Painters:
			painters_alg(object_data->polygon_list);
			break;
		default:
			break;
	}

	for (auto& p : object_data->polygon_list) 
		p->draw();

}

void Polyhedron::dump()
{
	auto *object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	for (auto& p : object_data->polygon_list)
		p->dump();
}

