//
//  polygon.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include <glm/glm.hpp>

#include "edge.hpp"

namespace Geometry {
	class Polygon : public Object
	{
		public:
			int xmin, xmax,
				ymin, ymax,
				zmin, zmax,
				num_vertices,
				num_edges;

			double D;

			glm::vec3 N, i;

			bool is_active;

			std::vector<int> ids;

			Polygon() = default;
			Polygon(int id, std::ifstream& data);
			Polygon(const Polygon& p);

			~Polygon() override = default;

			void update();
			void dump();
			std::vector<vertex_t> get_vertices();
			void draw() override;

	};
}

#endif /* polygon_hpp */