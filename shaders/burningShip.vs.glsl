#version 300 es
// #version 330 core
// #version 130
// #extension GL_ARB_explicit_attrib_location : require
// precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

layout (location = 0) in vec2 vPosition;


uniform parameters {
	float x0;
	float x1;
	float y0;
	float y1;
	float maxiter;
};

out vec4 color;

void main () {

	float x = x0 + (vPosition.x+1.0)*(x1-x0)/(2.0);
	float y = -(y0 + (vPosition.y+1.0)*(y1-y0)/(2.0));
	float zx = 0.0;
	float zy = 0.0;
	float temp;
	float k = 0.0;
	while ((sqrt (zx*zx+zy*zy) < 80.0) && (k < maxiter)) {
		temp = zx*zx - zy*zy + x;
		zy = 2.0 * abs(zx*zy) + y;
		zx = temp;
		k++;
	}

	gl_Position = vec4 (vPosition, 0.0, 1.0);
	color = vec4(0.6*(sin(0.05*k)+1.0), 1.0-k/maxiter, 1.0-k/maxiter, 1.0);
	// color = 1.0;
	// color = vec4 (x, y, 1, 1);
}
