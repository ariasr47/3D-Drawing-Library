//
//  vertex.hpp
//  3D_Drawing_System
//
//  Created by Rodrigo on 10/31/19.
//

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <fstream>

#include <glm/glm.hpp>
#include "object.h"

/* --------------------------------------------------------------------------------------------------------------------- */

/*

 Class Name: vertex
 Purpose: Represents a point in space as a triplet (x,y,z)
 Params: float x, float y, float z

*/

/* --------------------------------------------------------------------------------------------------------------------- */

#include "color.hpp"

namespace Geometry {
	class Vertex : public Object
	{
	public:

		glm::vec3 n, pos, I;

		Vertex() = default;
		Vertex(int id, std::ifstream& data, glm::vec3 clr = Black);
		Vertex(const Vertex& v);
		Vertex(double posx, double posy, double posz = 0);

		~Vertex() override = default;

		void draw() override {}

		bool operator==(const Vertex& v);
		glm::vec3 operator-(const Vertex& v);
	};
}

#endif /* vertex_hpp */