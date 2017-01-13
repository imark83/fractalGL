#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__

#include <GL/gl.h>

enum fractalIDs {BURNING_SHIP, MANDELBROT};

class Fractal {
public:
	int fractalID;
	void *pars;
	size_t npars;
	int nrow;
	int ncol;

	GLuint program, vao, vetexBuffer, blockBuffer;


	Fractal ();

	virtual void init () = 0;
	void render ();


};

#endif
