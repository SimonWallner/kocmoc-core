// Fragment Shader file "vertexColor.frag"
#version 120

varying vec3 color;

void main(void)
{
	gl_FragData[0] = vec4(color, 1);
}