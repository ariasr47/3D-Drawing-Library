//
//  utility.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "color.hpp"
#include "global.hpp"

/* initializes the drawing library */
void init();

/* loads object data if found */
void loadData();

/* draws the contents of the frame buffer */
void render();

/*  main loop callback function */
void user_interface();

bool is_consecutive(int x,  int y);

//using outer_bound = std::pair<int, edge_t>;

//std::pair<int, int> get_inner_bounds(int y, edge_t e1, edge_t e2);

//void get_outer_bounds(int y, edge_t e1, edge_t e2);

//std::pair<glm::vec3, glm::vec3> Interpolate(int y, outer_bound left, outer_bound right);

//glm::vec3 Interpolate(float x, float x1, float x2, glm::vec3 IL, glm::vec3 IR);

glm::vec3 computeIntensity(Geometry::Vertex P);

#endif /* UTILITY_HPP */