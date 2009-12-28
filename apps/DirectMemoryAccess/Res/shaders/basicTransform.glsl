//[VERT]
attribute vec3 position;
//attribute vec4 color;
attribute vec3 normal;
attribute vec2 texCoord0;

varying vec4 colorVar;
varying vec2 texCoord0Var;

uniform float time;
uniform float strength;
uniform float wireframe;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

#define PI 3.14159265

void main()
{
	vec4 pos = normalize(vec4(position, 1.0));
	pos.xyz +=  strength*0.1 * sin(time*-5.0 + texCoord0.t * 4.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 4.0 * PI) * normal;
	//pos.xyz +=  strength*0.1 * sin(time*10.0 + texCoord0.t * 8.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 8.0 * PI) * normal;
	float minLen = 1.0 - strength*0.3;
	float maxLen = 1.0 + strength*0.3;
	gl_Position = projectionMatrix * modelViewMatrix * pos;
	float depth = (length(pos)-minLen)/(maxLen-minLen);
	vec4 inside = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 outside = vec4(1.0, 1.0, 1.0, 1.0);
	colorVar = inside * (1.0-depth) + outside * depth;
	if (wireframe > 0.0) {
		colorVar = vec4(0.0, 0.0, 0.0, 1.0) * depth + colorVar * (1.0 - depth);		
		gl_Position.z -= 0.001;
	}
	//colorVar = vec4(texCoord0, 1.0, 1.0);
	//colorVar = vec4(0.5)+vec4(0.5*normalize(normal), 1.0);
	//colorVar = vec4(0.5)+pos*0.5;
	texCoord0Var = texCoord0;
}

//[FRAG]
varying lowp vec4 colorVar;
varying lowp vec2 texCoord0Var;

uniform sampler2D diffuseTex;

void main()
{
	lowp float d = 1.0/512.0;
	
	gl_FragColor = texture2D(diffuseTex, texCoord0Var);	
}
