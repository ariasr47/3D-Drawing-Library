#include "translate.h"

#include "global.hpp"
#include "data.hpp"
#include "vertex.hpp"

void translate(int obj_id, float tx, float ty, float tz)
{
	
	auto vertices = static_cast<polyhedron_data*>(db.object_data[obj_id].get())->vertex_list;

	for (auto x : vertices)
	{
		x->pos.x += tx;
		x->pos.y += ty;
		x->pos.z += tz;
	}
}
