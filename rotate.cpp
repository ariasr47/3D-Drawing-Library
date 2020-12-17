#include <corecrt_math_defines.h>
#include <glm/mat4x4.hpp>


#include "rotate.h"

#include "global.hpp"
#include "vertex.hpp"

void rotate(int obj_id, glm::vec3 p1, glm::vec3 p2, double angle)
{

	auto* object_data = static_cast<polyhedron_data*>(db.object_data[obj_id].get());

	glm::mat4x4 mat_quaternion_rot;
	glm::mat4x4 mat_rot;
	glm::mat4x4 mat_t;

	mat_t[0][3] = -p1.x;
	mat_t[1][3] = -p1.y;
	mat_t[2][3] = -p1.z;

	auto alpha = (angle * M_PI) / 180;

	auto axisVectLength = sqrt((p2.x - p1.x) * (p2.x - p1.x) +
		(p2.y - p1.y) * (p2.y - p1.y) +
		(p2.z - p1.z) * (p2.z - p1.z));

	auto cosA = cos(alpha);
	auto oneC = 1 - cosA;
	auto sinA = sin(alpha);

	auto ux = (p2.x - p1.x) / axisVectLength;
	auto uy = (p2.y - p1.y) / axisVectLength;
	auto uz = (p2.z - p1.z) / axisVectLength;

	mat_rot = mat_rot * mat_t;

	mat_quaternion_rot[0][0] = ux * ux * oneC + cosA;
	mat_quaternion_rot[0][1] = ux * uy * oneC - uz * sinA;
	mat_quaternion_rot[0][2] = ux * uz * oneC + uy * sinA;
	mat_quaternion_rot[1][0] = uy * ux * oneC + uz * sinA;
	mat_quaternion_rot[1][1] = uy * uy * oneC + cosA;
	mat_quaternion_rot[1][2] = uy * uz * oneC - ux * sinA;
	mat_quaternion_rot[2][0] = uz * ux * oneC - uy * sinA;
	mat_quaternion_rot[2][1] = uz * uy * oneC + ux * sinA;
	mat_quaternion_rot[2][2] = uz * uz * oneC + cosA;

	mat_rot = mat_quaternion_rot * mat_rot;

	mat_rot = inverse(mat_t) * mat_rot;

	for (auto v : object_data->vertex_list)
	{
		glm::vec4 p0(v->pos.x, v->pos.y, v->pos.z, 1);
		auto result = mat_rot * p0;
		v->pos.x = result.x;
		v->pos.y = result.y;
		v->pos.z = result.z;
	}

	// update();
}
