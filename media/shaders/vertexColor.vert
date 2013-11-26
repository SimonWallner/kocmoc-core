// vertex Shader vertexColor.vert

#version 120

attribute vec4 inPosition;
attribute vec3 inColor;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec3 color;


void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * inPosition;
	color = inColor * 1000;
}