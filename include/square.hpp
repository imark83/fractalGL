#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include <GL/gl.h>

class Square {
  float p[8];

	GLuint program, vao, vetexBuffer, blockBuffer;

  Square (float xy0[2], float xy1[2]) {
    p[0] = xy0[0];
    p[1] = xy0[1];
    p[2] = xy1[0];
    p[3] = xy0[1];
    p[4] = xy1[0];
    p[5] = xy1[1];
    p[6] = xy0[0];
    p[7] = xy1[1];
  }

	void init () {
		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER, "shaders/default.vs.glsl"},
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

}

#endif
