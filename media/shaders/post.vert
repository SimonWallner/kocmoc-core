// Vertex Shader – file "base.vert"

#version 120

attribute vec3 inPosition;
attribute vec2 inUv;

varying vec2 uv;

void main(void)
{
	gl_Position = vec4(inPosition, 1.0f);
	uv = inUv;
}
