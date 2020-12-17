//
//  paintersAlg.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/28/19.
//

#include <algorithm>
#include "polygon.hpp"
#include "data.hpp"

#include "paintersAlg.hpp"

using test_fn = bool(*)(polygon_t& Oi, polygon_t& Sk);

bool depth_overlap(polygon_t& Oi, polygon_t& Sk)
{
	return !(Sk->zmin < Oi->zmax);
}

bool xy_overlap(polygon_t& Oi, polygon_t& Sk) {
	return Oi->xmin > Sk->xmax ||
		Sk->xmin > Oi->xmax ||
		Oi->ymin > Sk->ymax ||
		Sk->ymin > Oi->ymax;
}

bool behind(polygon_t& Oi, polygon_t& Sk) {

	for (auto P : Sk->get_vertices()) {
		auto result = Oi->N.x * P->pos.x + Oi->N.y * P->pos.y + Oi->N.z * P->pos.z + Oi->D;
		if ( ( Sk->N.z < 0 ? -result : result) > 0)
			return false;
	}

	return true;
}

bool front(polygon_t& Oi, polygon_t& Sk) {
	
	for (auto P : Oi->get_vertices()) {
		auto result = Sk->N.x * P->pos.x + Sk->N.y * P->pos.y + Sk->N.z * P->pos.z + Sk->D;
		if ( ( Sk->N.z < 0 ? -result : result) < 0)
			return false;
	}

	return true;
}

bool boundary_edge(polygon_t& Oi, polygon_t& Sk) {
	// TODO: Implement boundary edge test
	return true;
}


bool test_all(std::vector<r_iter>& O, r_iter Sk)
{
	auto tests = std::vector<test_fn>{ xy_overlap, behind, front, boundary_edge };
	std::vector<int> passed(0, O.size());
	for (auto i = 0; i < O.size(); i++) {
		
		for (auto test : tests)
			if (test(*O[i], *Sk))
				passed[i] += 1;
		
		if (passed[i] == 0) {
			std::iter_swap(O[i], Sk);
			break;
		}
	}

	auto all_tests_passed = std::find(std::begin(passed), std::end(passed), 0) != std::end(passed);

	return all_tests_passed;
}


void painters_alg(std::vector<polygon_t>& polygon_list){

	
	std::sort(polygon_list.begin(),polygon_list.end(),[](auto &lhs, auto &rhs) {
		return lhs->zmin > rhs->zmin;
	});

	
	for (auto Sk = polygon_list.rbegin(); Sk != polygon_list.rend(); Sk++) {
		std::vector<r_iter> O;

		for (r_iter Oi = Sk + 1; Oi != polygon_list.rend(); Oi++)
			if (depth_overlap(*Oi, *Sk))
				O.emplace_back(Oi);

		if (O.empty() || test_all(O, Sk))
			(*Sk)->draw();
	}
	
}

