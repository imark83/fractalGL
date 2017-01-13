#ifndef __BURNING_SHIP_HPP__
#define __BURNING_SHIP_HPP__

#include <fractal.hpp>

class BurningShip : public Fractal {
public:

	BurningShip (int = 0, int = 0);

	int nPoint () {return nrow * ncol;}

	void init () {
		// glPointSize (3);
		glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER, "shaders/burningShip.vs.glsl"},
			{GL_FRAGMENT_SHADER, "default.fs.glsl"},
			{GL_NONE, NULL}};
		program = loadShaders (shaders);
		glUseProgram(program);

		GLfloat *p = new GLfloat[2*nPoint()];
		for (int i=0; i<nrow; ++i) for (int j=0; j<ncol; ++j) {
			p[2*(ncol*i+j)] = (2.0*i)/((GLfloat) nrow)-1.0;
			p[2*(ncol*i+j)+1] = (2.0*j)/((GLfloat) ncol)-1.0;
		}
		glGenVertexArrays (1, &vao);
		glBindVertexArray (vao);


		glGenBuffers (1, &parBuffer);
		glBindBuffer (GL_UNIFORM_BUFFER, parBuffer);

		glBufferData (GL_UNIFORM_BUFFER, 5*sizeof (GLfloat), pars, GL_STATIC_DRAW);
		glBindBufferBase (GL_UNIFORM_BUFFER, glGetUniformBlockIndex (program, "parameters"), parBuffer);


		glGenBuffers (1, &buffer);
		glBindBuffer (GL_ARRAY_BUFFER, buffer);
		glBufferData (GL_ARRAY_BUFFER, nPoint()*2*sizeof (GLfloat), p, GL_STATIC_DRAW);


		glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
					(const void*) 0);
		glEnableVertexAttribArray (0);




		// glUniform1f (glGetUniformLocation(program, "x0"), x0);
		// glUniform1f (glGetUniformLocation(program, "x1"), x1);
		// glUniform1f (glGetUniformLocation(program, "y0"), y0);
		// glUniform1f (glGetUniformLocation(program, "y1"), y1);
		// glUniform1f (glGetUniformLocation(program, "maxiter"), maxiter);


		delete [] p;
	}


};

#endif
