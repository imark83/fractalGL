#version 300 es
precision highp float; 		// Defines precision for
							// float and float-derived
							// (vector/matrix) types.



in float color;

out vec4 fColor;

void main () {
	fColor = vec4(1.0, 1.0 ,1.0, 1);
}
