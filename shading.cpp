//
//  shading.cpp
//  drawinglib
//
//  Created by Rodrigo on 12/3/19.
//


#include "polygon.hpp"

#include "data.hpp"

#include "shading.hpp"

#include "utility.hpp"

#include "line.hpp"

#include "../../../../Desktop/DrawingLibrary/object/color.hpp"

using namespace Geometry;

void flat_shading(Geometry::Polygon* p) {
	auto edge_table = static_cast<polyhedron_data*>(db.object_data[p->get_id()].get())->edge_table;
	auto pixel_locations = std::map<int, std::set<edge_point, std::less<>>>();
	for (auto& [key,e] : edge_table) {
		auto [v1, v2] = e->get_vertices();
		DrawLine(v1, v2, pixel_locations);
	}
	
	for (auto [y, values] : pixel_locations)
	{
		auto left = *values.begin(),
			 right = *values.rbegin();

		for (auto x = left.x; x <= right.x; x++) 
			MakePixel(x, y, color::red);
	}
}

void gouraud_shading(Geometry::Polygon* p) {
	auto I1 = Green,
		 I2 = Blue,
		 I3 = White;
	
	auto edge_table = static_cast<polyhedron_data*>(db.object_data[p->get_id()].get())->edge_table;
	auto pixel_locations = std::map<int, std::set<edge_point, std::less<>>>();
	
	for (auto& [key, e] : edge_table) {
		auto [v1, v2] = e->get_vertices();
		DrawLine(v1, v2, pixel_locations);
	}

	for (auto [y, values] : pixel_locations)
	{
		auto left = *values.begin(),
			 right = *values.rbegin();

		auto IL = left.delta1 * I1 + left.delta2 * I2;
		auto IR = right.delta1 * I1 + right.delta2 * I3;
		
		for (auto x = left.x; x <= right.x; x++) {
			auto diff = right.x - left.x;
			auto I = (float(right.x - x) / diff) * IL + (float(x - left.x) / diff) * IR;
			MakePixel(x, y, I);
		}
	}
}

void phong_lighting(Geometry::Polygon* p) {
	return;
}