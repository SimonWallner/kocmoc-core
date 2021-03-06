#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;
uniform sampler3D sColourLUT;

uniform ivec2 dimension;
uniform float angleOfView;
uniform float averageLuminance;
uniform int lutSize;

const float HDRcontrast = 6.0f;
const float HDRbias = 1.5f;

vec4 tonemap(vec4 hdr)
{
	vec3 c = hdr.rgb;
	float low = exp(averageLuminance - HDRbias - HDRcontrast/2.0f);
	float high = exp(averageLuminance - HDRbias + HDRcontrast/2.0f);

	vec3 ldr = (hdr.rgb - low) / (high - low);
	return vec4(ldr, hdr.a);
}

vec3 colorWarn(vec3 c)
{
	vec3 warn = c;
	if (c.r > 1.0f || c.g > 1.0f || c.b > 1.0f)
	{
		warn.r = 1;
		warn.g = 0;
	}
	if (c.r < 0.0f || c.g < 0.0f || c.b < 0.0f)
	{
		warn.b = 1.0;
		warn.g = 0;
	}
	return warn;
}

void main(void)
{
	const float barrelParam = 0.6;
	float aspectRatio = dimension.x / dimension.y;

	vec4 colour;


	// === non planar projection ===
	float scale = tan(angleOfView/2 * barrelParam);		
	vec2 normalizedUV = (uv * 2 - 1) / vec2(1, aspectRatio); // to [-1, 1] and square pixels

	vec2 angle = normalizedUV * (angleOfView/2 * barrelParam);
	vec2 bentUV = angle / (length(angle) / tan(length(angle))) / scale;

	vec2 finalUV = (bentUV * vec2(1, aspectRatio)) / 2 + 0.5f;


	// 5 tap multi sampling...
	vec2 msaaOffset = 0.5f * 1.0f/dimension;
	vec4 c = texture2D(sDiffuse, finalUV);
	c += texture2D(sDiffuse, finalUV + msaaOffset);
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(1.0f, -1.0f));
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(-1.0f, 1.0f));
	c += texture2D(sDiffuse, finalUV + msaaOffset * vec2(-1.0f, -1.0f));
	colour = c / 5.0f;	
	// colour = texture2D(sDiffuse, uv);


	// === vignetting ===
	float attenuation = 0.3f;
	float power = 1.7;

	float delta = distance((uv - vec2(0.5, 0.5)) / vec2(1, aspectRatio), vec2(0, 0)) * 2.0f;
	float darkening = 1 - pow(delta, power) * attenuation;
	// colour = colour * vec4(vec3(darkening), 1);

	// hdr tonemapping 
	colour = tonemap(colour);
	// gl_FragColor = vec4(colorWarn(colour.rgb), 1);
	
	colour = texture3D(sColourLUT, colour.rgb * ((lutSize - 1.0f) / (lutSize)) + (0.5f / lutSize));
	
	gl_FragColor = colour;

}
