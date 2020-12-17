//
//  main.cpp
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#include "utility.hpp"

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	init();

	glutDisplayFunc(user_interface);

	glutMainLoop();

	return 0;
}