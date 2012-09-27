#version 120

#pragma include luminance.glsl
varying vec2 uv;

uniform sampler2D sDiffuse;

uniform ivec2 dimension;
uniform float angleOfView;
uniform float averageLuminance;

const float HDRcontrast = 6.0f;
const float HDRbias = 1.0f;

vec4 tonemap(vec4 hdr)
{
	vec3 c = hdr.rgb;
	float low = exp(averageLuminance - HDRbias - HDRcontrast/2.0f);
	float high = exp(averageLuminance - HDRbias + HDRcontrast/2.0f);

	vec3 ldr = (hdr.rgb - low) / (high - low);
	return vec4(ldr, hdr.a);
}

void main(void)
{
//	const float barrelParam = 0.7;
	const float barrelParam = 0.8;
	float aspectRatio = dimension.x / dimension.y;

	vec4 color;


	// === non planar projection ===
	float scale = tan(angleOfView/2 * barrelParam);		
	vec2 normalizedUV = (uv * 2 - 1) / vec2(1, aspectRatio); // to [-1, 1] and square pixels

	vec2 angle = normalizedUV * (angleOfView/2 * barrelParam);
	vec2 bentUV = angle / (length(angle) / tan(length(angle))) / scale;

	vec2 finalUV = (bentUV * vec2(1, aspectRatio)) / 2 + 0.5f;


	// 4 tab multi sampling...
	vec2 msaaOffset = 0.5f * 1.0f/dimension;
	vec4 c = texture2D(sDiffuse, finalUV + msaaOffset);
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(-1.0f, 1.0f));
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(1.0f, -1.0f));
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(-1.0f, -1.0f));
	color = c / 4.0f;	


	// === vignetting ===
	float attenuation = 0.3f;
	float power = 1.7;

	float delta = distance((uv - vec2(0.5, 0.5)) / vec2(1, aspectRatio), vec2(0, 0)) * 2.0f;
	float darkening = 1 - pow(delta, power) * attenuation;
	color = color * vec4(vec3(darkening), 1);

	// hdr tonemapping 
	color = tonemap(color);
	
	gl_FragColor = color;
}
