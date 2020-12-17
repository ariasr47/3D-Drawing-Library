//
//  global.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#include <iostream>

#include "global.hpp"
#include "data.hpp"

const char* filename = "data.txt";

// Window settings
const int window_width = 500;
const int window_height = 500;

// Buffer settings
const int buffer_height = 500;
const int buffer_width = 500;
const int buffer_size = buffer_height * buffer_width * 3;

// Light settings
glm::vec3 ka;
glm::vec3 kd;
glm::vec3 ks;
glm::vec3 x,f;

float Ia;
float Il;

// Algorithm settings
LineAlg line_alg;
VisibilityAlg vis_alg;
ShadingAlg shading_alg;

// Buffer used to write to frame buffer
GLubyte* pixel_buffer = new GLubyte[buffer_size];

// Objects in scene
DataBase db;