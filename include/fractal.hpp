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


	void reset () {
		pars[0] = -1.82; 	// x0
		pars[1] = -1.54; 	// x1
		pars[2] = -0.03; 	// y0
		pars[3] = 0.1;	 	// y1
		pars[4] = 120.0; 	// maxiter

		glBindBuffer (GL_UNIFORM_BUFFER, blockBuffer);
		glBufferData (GL_UNIFORM_BUFFER, npars*sizeof (GLfloat), pars, GL_STATIC_DRAW);

	}

	void init () {
		int npoint = nrow * ncol;

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
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		int npoint = nrow * ncol;
		glDrawArrays(GL_POINTS, 0, npoint);
	}

	void zoom (float x0, float y0, float x1, float y1) {
		glBindBuffer (GL_UNIFORM_BUFFER, blockBuffer);
		float width = pars[1] - pars[0];
		float height = pars[3] - pars[2];


		if (x0>x1) {
			float aux = x1; x1 = x0; x0 = aux;
		}

		y0 = -y0; y1 = -y1;
		if (y0>y1) {
			float aux = y1; y1 = y0; y0 = aux;
		}


		std::cout << "y0 = " << pars[2] << ", height = " << height << std::endl;
		std::cout << "y1 = " << pars[3] << ", height = " << height << std::endl;


		pars[1] = pars[0] + (x1+1.0f)/2.0*width;
		pars[0] += (x0+1.0f)/2.0*width;


		pars[3] = pars[2] + (y1+1.0f)/2.0*height;
		pars[2] += (y0+1.0f)/2.0*height;


		std::cout << "y0 = " << pars[2] << ", height = " << height << std::endl;
		std::cout << "y1 = " << pars[3] << ", height = " << height << std::endl;

		glBufferData (GL_UNIFORM_BUFFER, npars*sizeof (GLfloat), pars, GL_STATIC_DRAW);

	}

};

#endif
