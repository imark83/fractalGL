#version 300 es
// #version 330 core
// #version 130
// #extension GL_ARB_explicit_attrib_location : require
// precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

layout (location = 0) in vec2 vPosition;



out float color;

void main () {
	float x0 = -1.82;
	float x1 = -1.54;
	float y0 = -0.2;
	float y1 = 0.1;
	int width = 512;
	int height = 512;
	int maxiter = 80;

	float x = x0 + (vPosition.x+1.0)/2.0;
	float y = y0 + (vPosition.y+1.0)/2.0;
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
	color = cos(k);

	gl_Position = vec4 (vPosition, 0.0, 1.0);
	// color = 1.0;
}
