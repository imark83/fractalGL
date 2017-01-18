#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__

#include <GL/gl.h>

enum fractalIDs {BURNING_SHIP, MANDELBROT};

class Fractal {
public:
	int fractalID;
	float *pars;
	size_t npars;
	int nrow;
	int ncol;

	GLuint program, vao, vetexBuffer, blockBuffer;


	Fractal () {
		fractalID = BURNING_SHIP;
		npars = 5;

		pars = new float [npars];
		pars[0] = -1.82; 	// x0
		pars[1] = -1.54; 	// x1
		pars[2] = -0.03; 	// y0
		pars[3] = 0.1;	 	// y1
		pars[4] = 120.0; 	// maxiter

		nrow = 1920;
		ncol = 1080;
	}

	~Fractal () {
		delete [] pars;
	}



	void init () {
		int npoint = nrow * ncol;
		// glPointSize (3);
		glClearColor (0.0f, 0.0f, 0.0f, 0.0f);


		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER, "shaders/burningShip.vs.glsl"},
			{GL_FRAGMENT_SHADER, "shaders/default.fs.glsl"},
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


		glGenBuffers (1, &blockBuffer);
		glBindBuffer (GL_UNIFORM_BUFFER, blockBuffer);

		glBufferData (GL_UNIFORM_BUFFER, npars*sizeof (GLfloat), pars, GL_STATIC_DRAW);
		glBindBufferBase (GL_UNIFORM_BUFFER, glGetUniformBlockIndex (program, "parameters"), blockBuffer);


		glGenBuffers (1, &vetexBuffer);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		glBufferData (GL_ARRAY_BUFFER, npoint*2*sizeof (GLfloat), p, GL_STATIC_DRAW);


		glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
					(const void*) 0);
		glEnableVertexAttribArray (0);


		delete [] p;
	}
	void render () {
		int npoint = nrow * ncol;
		glClear (GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, npoint);
		glFlush ();
		std::cout << "vao = "  << vao << std::endl;
		std::cout << "buffer = "  << vetexBuffer << std::endl;
		std::cout << "npoint = "  << npoint << std::endl;
	}


};

#endif
