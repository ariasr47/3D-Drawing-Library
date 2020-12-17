//
//  line.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/28/19.
//

#include <cmath>

#include "line.hpp"
#include "global.hpp"
#include "vertex.hpp"

void MakePixel(int x, int y, glm::vec3 rgb)
{
	if (x >= 0 && y >= 0 && x < buffer_width && y < buffer_height) {
		pixel_buffer[(buffer_width * y + x) * 3] = (unsigned char) round(rgb.r);
		pixel_buffer[(buffer_width * y + x) * 3 + 1] = (unsigned char) round(rgb.g);
		pixel_buffer[(buffer_width * y + x) * 3 + 2] = (unsigned char) round(rgb.b);
	}
}

void DrawLine(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations) {
	switch (line_alg) {
		case LineAlg::DDA:
			return(DDA(v1, v2, pixel_locations));
		case LineAlg::Bresenham:
			return(Bresenham(v1, v2, pixel_locations));
	}
}

void DDA(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations)
{
	const auto x1 = round(v1->pos.x),
		x2 = round(v2->pos.x),
		y1 = round(v1->pos.y),
		y2 = round(v2->pos.y);

	const auto dx = static_cast<int>(x2 - x1),
		dy = static_cast<int>(y2 - y1);

	auto step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	const auto x_step = static_cast<float>(dx) / step;
	const auto y_step = static_cast<float>(dy) / step;

	auto x = x1,
		 y = y1;

	for (auto i = 0; i <= step; i++) {
		x = x1 + x_step * i;
		y = y1 + y_step * i;
		
		const auto value = static_cast<int>(round(x)),
			key = static_cast<int>(round(y));
		
		if (pixel_locations.count(key) == 0) 
			pixel_locations[key] = std::set<edge_point, std::less<>>();
		
		pixel_locations[key].insert(edge_point(y2, y1, value, key));
		MakePixel(value, key);
	}
}

void Bresenham(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations)
{
	int x1 = (round(v1->pos.x)), y1 = (round(v1->pos.y)),
		x2 = (round(v2->pos.x)), y2 = (round(v2->pos.y)),
		dx = (x2 - x1), dy = (y2 - y1);

	double slope = (dx != 0) ? (double)dy / dx : 0;

	dx = abs(dx);
	dy = abs(dy);

	int p = abs(slope) < 1 ? 2 * dy - dx : 2 * dx - dy;
	int dy2 = 2 * dy;
	int dy2_dx = 2 * (dy - dx);
	int dx2 = 2 * dx;
	int dx2_dy = 2 * (dx - dy);

	int x = x1,
		y = y1;

	if (dx == 0) {
		for (int i = 0; i <= dy; i++)
			MakePixel(x1, y1 + i);
	}
	else if (abs(slope) < 1) {
		if (x1 > x2) {
			x = x2;
			y = y2;
			x2 = x1;
		}

		MakePixel(x, y);

		while (x < x2) {
			if (p < 0) {
				p += dy2;
			}
			else {
				slope > 0 ? y++ : y--;
				p += dy2_dx;
			}
			MakePixel(++x, y);
		}
	}
	else {
		if (y1 > y2) {
			x = x2;
			y = y2;
			y2 = y1;
		}

		MakePixel(x, y);

		while (y < y2) {
			if (p < 0) {
				p += dx2;
			}
			else {
				slope > 0 ? x++ : x--;
				p += dx2_dy;
			}
			MakePixel(x, ++y);
		}
	}
}