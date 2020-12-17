//
//  global.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <glm/glm.hpp>
#include <GL/freeglut_std.h>

#include "data.hpp"

enum class LineAlg : char
{
	DDA = '1',
	Bresenham = '2'
};

enum class VisibilityAlg : char
{
	Painters = '1',
	BackFaceCulling = '2'
};

enum class ShadingAlg : char
{
	FlatShading = '1',
	GouradShading = '2',
	PhongLightingModel = '3'
};

extern const char* filename;

// Window settings
extern const int window_width;
extern const int window_height;

// Buffer settings
extern const int buffer_height;
extern const int buffer_width;
extern const int buffer_size;

// Algorithm settings
extern LineAlg line_alg;
extern VisibilityAlg vis_alg;
extern ShadingAlg shading_alg;

// Buffer
extern GLubyte* pixel_buffer;

// Light position
extern glm::vec3 x;

// From position
extern glm::vec3 f;

extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;

extern float Ia;
extern float Il;

extern DataBase db;

#endif /* global_hpp */