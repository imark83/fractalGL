#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include <loadShaders.h>


GLuint vao;
GLuint program;
GLuint buffer;

int nrow = 1024;
int ncol = 1024;
int npoint;


float x0 = -1.82;
float x1 = -1.54;
float y0 = -0.03;
float y1 = 0.1;
float maxiter = 120.0;




void renderFunction() {
	glClear (GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, npoint);
	glFlush ();
	std::cout << "vao = "  << vao << std::endl;
	std::cout << "buffer = "  << buffer << std::endl;
	std::cout << "npoint = "  << npoint << std::endl;
}


void init () {
	npoint = nrow * ncol;
	// glPointSize (3);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "fractal.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};
	program = loadShaders (shaders);
	glUseProgram(program);

	GLfloat *p = new GLfloat[2*npoint];
	for (int i=0; i<nrow; ++i) for (int j=0; j<ncol; ++j) {
		p[2*(ncol*i+j)] = (2.0*i)/((GLfloat) nrow)-1.0;
		p[2*(ncol*i+j)+1] = (2.0*j)/((GLfloat) ncol)-1.0;
	}



	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glGenBuffers (1, &buffer);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);

	glBufferData (GL_ARRAY_BUFFER, npoint*2*sizeof (GLfloat), p, GL_STATIC_DRAW);

	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
				(const void*) 0);
	glEnableVertexAttribArray (0);


	glUniform1f (glGetUniformLocation(program, "x0"), x0);
	glUniform1f (glGetUniformLocation(program, "x1"), x1);
	glUniform1f (glGetUniformLocation(program, "y0"), y0);
	glUniform1f (glGetUniformLocation(program, "y1"), y1);
	glUniform1f (glGetUniformLocation(program, "maxiter"), maxiter);


	delete [] p;
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA);
	glutInitWindowSize(1024,1024);
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
