// Fragment Shader file "text.frag"

#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;

void main(void)
{
	vec4 c = texture2D(sDiffuse, uv);
	gl_FragColor = vec4(0, 0, 0, c.r);
}