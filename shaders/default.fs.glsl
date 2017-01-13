#version 300 es
precision highp float; 		// Defines precision for
							// float and float-derived
							// (vector/matrix) types.



in vec4 color;

out vec4 fColor;

void main () {
	fColor = color;
}
