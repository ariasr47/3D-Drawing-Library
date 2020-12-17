//
//  edge.hpp
//  3D_Drawing_System
//
//  Created by Rodrigo on 10/31/19.
//  Copyright © 2019 UC Davis. All rights reserved.
//

#ifndef EDGE_HPP
#define EDGE_HPP

#include "data.hpp"
#include "vertex.hpp"

namespace Geometry {
	class Edge : public Object
	{
	public:
		int v1, v2,
			xmin, xmax,
			ymin, ymax,
			zmin, zmax,
			dx, dy,
			step;

		double xstep, ystep;

		bool is_active = false;
		bool is_drawn = false;

		// constructors
		Edge();
		Edge(int id, int id1, int id2);
		Edge(const Edge&);

		// destructor
		~Edge() override = default;

		// utility
		std::pair < vertex_t, vertex_t> get_vertices();
		void update();
		void draw() override;
		bool operator==(const Edge& e);
	};
}

#endif /* EDGE_HPP */