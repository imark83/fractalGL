#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include <loadShaders.h>
#include <fractal.hpp>
#include <square.hpp>

Fractal fractal;
Square square (-0.5,-0.5,0.5,0.5);

void renderFunction() {
	// glClear (GL_COLOR_BUFFER_BIT);
	fractal.render();
	square.render();
	glFlush ();
}


void init () {
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	fractal.init();
	square.init();
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize(1920,1080);
	glutInitWindowPosition(0, 0);


	glutCreateWindow("Fractal");
	glewInit();

	glutDisplayFunc(renderFunction);
	// glutIdleFunc (renderFunction);

	init ();
	renderFunction ();
	glutMainLoop();

	return 0;
}
