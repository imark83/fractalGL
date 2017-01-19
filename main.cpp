#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include <loadShaders.h>
#include <fractal.hpp>


Fractal fractal;

void renderFunction() {
	fractal.render();
}


void init () {
	fractal.init();
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize(1920,1080);
	glutInitWindowPosition(500, 100);


	glutCreateWindow("Fractal");
	glewInit();

	glutDisplayFunc(renderFunction);
	// glutIdleFunc (renderFunction);

	init ();
	renderFunction ();
	glutMainLoop();

	return 0;
}
