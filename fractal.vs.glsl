#version 300 es
// #version 330 core
// #version 130
// #extension GL_ARB_explicit_attrib_location : require
// precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

layout (location = 0) in vec2 vPosition;


uniform float x0;
uniform float x1;
uniform float y0;
uniform float y1;

out float color;

void main () {
	gl_Position = vec4 (vPosition, 0.0, 1.0);
	float x = 1;

	color = 1.0;
}
