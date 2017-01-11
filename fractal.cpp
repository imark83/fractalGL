#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "loadShaders.h"


GLuint vao;
GLuint program;
GLuint buffer;


void renderFunction() {
	/* code */
}


void init () {
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "fractal.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};
	loadShaders (shaders);

	GLfloat *p = new GLfloat[2*500*500];
	for (int i=0; i<500; ++i) for (int j=0; j<500; ++j) {
		p[500*i+j] = i/500.0; p[500*i+j] = j/500.0;
	}


	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glGenBuffers (1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);

	glBufferData (GL_ARRAY_BUFFER, 500*500*2*sizeof (GLfloat), p, GL_STATIC_DRAW);



	delete [] p;
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500, 100);


	glutCreateWindow("Fractal");
	glewInit();

	glutDisplayFunc(renderFunction);
	glutIdleFunc (renderFunction);

	init ();
	glutMainLoop();

	return 0;
}
