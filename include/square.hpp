#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include <GL/gl.h>

class Square {
public:
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

	Square (float x0, float y0, float x1, float y1) {
		p[0] = x0;
		p[1] = y0;
		p[2] = x1;
		p[3] = y0;
		p[4] = x1;
		p[5] = y1;
		p[6] = x0;
		p[7] = y1;
	}

	void init () {
		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER, "shaders/default.vs.glsl"},
			{GL_FRAGMENT_SHADER, "shaders/default.fs.glsl"},
			{GL_NONE, NULL}};
		program = loadShaders (shaders);
		glUseProgram(program);

		glGenVertexArrays (1, &vao);
		glBindVertexArray (vao);

		glGenBuffers (1, &vetexBuffer);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		glBufferData (GL_ARRAY_BUFFER, 8*sizeof (GLfloat), p, GL_STATIC_DRAW);

		glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
					(const void*) 0);
		glEnableVertexAttribArray (0);
	}

	void render () {
		glUseProgram(program);
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

	}

	void setXY0 (float x0, float y0) {
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		p[0] = p[6] = x0;
		p[1] = p[3] = y0;
		glBufferData (GL_ARRAY_BUFFER, 8*sizeof (GLfloat), p, GL_STATIC_DRAW);
	}

	void setXY1 (float x1, float y1) {
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vetexBuffer);
		p[2] = p[4] = x1;
		p[5] = p[7] = y1;
		glBufferData (GL_ARRAY_BUFFER, 8*sizeof (GLfloat), p, GL_STATIC_DRAW);
	}

	float getX0 () {
		return (p[0]<p[2]) ? p[0] : p[1];
	}

	float getX1 () {
		return (p[0]>p[2]) ? p[0] : p[1];
	}

	float getY0 () {
		return (p[1]<p[7]) ? p[1] : p[7];
	}

	float getY1 () {
		return (p[1]>p[7]) ? p[1] : p[7];
	}

};

#endif
