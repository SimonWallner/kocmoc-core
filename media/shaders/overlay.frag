// Fragment Shader file "overlay.frag"

#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;

void main(void)
{
	gl_FragColor = vec4(1, 1, 0, 1);
}