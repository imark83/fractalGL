#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include <loadShaders.h>
#include <fractal.hpp>
#include <square.hpp>

Fractal fractal;
Square square (-0.5,-0.5,0.5,0.5);
struct windowSize_t {
	int x;
	int y;
};
windowSize_t windowSize = {1920, 1080};

void renderFunction() {
	// glClear (GL_COLOR_BUFFER_BIT);
	fractal.render();
	glFlush ();
}


void init () {
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	fractal.init();
	square.init();
}

void mouseClick(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) {
		fractal.reset();
		fractal.render();
		glFlush();
		return;
	}
	switch (state) {
		case GLUT_DOWN:
			square.setXY0 ((2.0f*x)/windowSize.x - 1.0f,
		 				1.0f - (2.0f*y)/windowSize.y);
			square.setXY1 ((2.0f*x)/windowSize.x - 1.0f,
		 				1.0f - (2.0f*y)/windowSize.y);
			break;
		case GLUT_UP:
			square.setXY1 ((2.0f*x)/windowSize.x - 1.0f,
		 				1.0f - (2.0f*y)/windowSize.y);
			fractal.zoom (square.getX0(), square.getY0(),
						square.getX1(), square.getY1());
			break;
	}

	fractal.render();
	glFlush();
}




int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize(windowSize.x,windowSize.y);
	glutInitWindowPosition(0, 0);


	glutCreateWindow("Fractal");
	glewInit();

	glutDisplayFunc(renderFunction);
	glutMouseFunc(mouseClick);

	// glutIdleFunc (renderFunction);

	init ();
	renderFunction ();
	glutMainLoop();

	return 0;
}
