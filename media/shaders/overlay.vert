// vertex Shader overlay.vert

#version 120

attribute vec3 inPosition;
attribute vec2 inUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec2 uv;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1);
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;	
	
	uv = inUv;
}