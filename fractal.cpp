#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "loadShaders.h"


GLuint vao;
GLuint program;
GLuint buffer;

int nrow = 512;
int ncol = 512;
int npoint;




void renderFunction() {
	glClear (GL_COLOR_BUFFER_BIT);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	glDrawArrays(GL_POINTS, 0, npoint);
	glFlush ();
	std::cout << "vao = "  << vao << std::endl;
	std::cout << "buffer = "  << buffer << std::endl;
	std::cout << "npoint = "  << npoint << std::endl;
}


void init () {
	npoint = nrow * ncol;
	glPointSize (3);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "fractal.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};
	program = loadShaders (shaders);
	glUseProgram(program);

	GLfloat *p = new GLfloat[2*npoint];
	for (int i=0; i<nrow; ++i) for (int j=0; j<ncol; ++j) {
		p[ncol*i+j] = (1.0*i)/((GLfloat) nrow); p[ncol*i+j] = (1.0*j)/((GLfloat) ncol);
	}


	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glGenBuffers (1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);

	for (int i=0; i<nrow; ++i) for (int j=0; j<ncol; ++j) {
		p[2*(ncol*i+j)] = (2.0*i)/((GLfloat) nrow) - 1.0; p[2*(ncol*i+j)+1] = (2.0*j)/((GLfloat) ncol) - 1.0;
	}


	glBufferData (GL_ARRAY_BUFFER, npoint*2*sizeof (GLfloat), p, GL_STATIC_DRAW);

	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
				(const void*) 0);
	glEnableVertexAttribArray (0);



	delete [] p;
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize(512,512);
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
