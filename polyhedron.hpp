//
//  polyhedron.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#ifndef POLYHEDRON_HPP
#define POLYHEDRON_HPP

#include "object.h"

namespace Geometry {
	class Polyhedron : public Object {
	public:
		// constructors
		Polyhedron() = default;
		Polyhedron(int id, std::ifstream& data);
		Polyhedron(Polyhedron& p);

		// destructor
		~Polyhedron() override = default;

		// utility
		void dump();
		void draw() override;

	private:
		void update();
	};
}

#endif /* POLYHEDRON_HPP */