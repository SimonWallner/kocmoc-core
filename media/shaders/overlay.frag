// Fragment Shader file "overlay.frag"

#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;

void main(void)
{
	gl_FragColor = texture2D(sDiffuse, uv);
}