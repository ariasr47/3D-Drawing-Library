//
//  line.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/28/19.
//

#ifndef LINE_HPP
#define LINE_HPP

#include <map>

#include "color.hpp"
#include <set>

#include "data.hpp"

class edge_point {
public:
	edge_point(int y2, int y1, int x, int y) : x(x)
	{
		auto diff = y2 - y1;
		delta1 = (diff == 0) ? 0 : float(y - y1) / diff;
		delta2 = (diff == 0) ? 0 : float(y2 - y) / diff;
		
	}
	
	float delta1, delta2;
	int x;
};

inline bool operator<(const edge_point& ep1, const edge_point& ep2) {
	return ep1.x < ep2.x;
}

void MakePixel(int x, int y, glm::vec3 rgb = Black);

void DDA(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations);

void Bresenham(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations);

void DrawLine(vertex_t v1, vertex_t v2, std::map<int, std::set<edge_point, std::less<>>>& pixel_locations);

#endif /* line_hpp */