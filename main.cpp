#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include <loadShaders.h>
#include <fractal.hpp>


GLuint vao;
GLuint program;
GLuint buffer;
GLuint parBuffer;

int nrow = 1920;
int ncol = 1080;
int npoint;



float x0 = -1.82;
float x1 = -1.54;
float y0 = -0.03;
float y1 = 0.1;
float maxiter = 120.0;


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
