//[VERT]
attribute vec3 position;
//attribute vec4 color;
attribute vec3 normal;
attribute vec2 texCoord0;

varying vec4 colorVar;
varying vec2 texCoord0Var;
varying vec3 normalVar;

uniform float time;
uniform float strength;
uniform float wireframe;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform mat4 invModelviewMatrix;

#define PI 3.14159265

void main()
{
	vec4 pos = normalize(vec4(position, 1.0));
	pos.xyz +=  strength*0.1 * sin(time*-5.0 + texCoord0.t * 4.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 4.0 * PI) * normal;	
	float minLen = 1.0 - strength*0.3;
	float maxLen = 1.0 + strength*0.3;
	gl_Position = projectionMatrix * modelviewMatrix * pos;
	
	
	float depth = (length(pos)-minLen)/(maxLen-minLen);
	vec4 inside = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 outside = vec4(1.0, 1.0, 1.0, 1.0);
	colorVar = inside * (1.0-depth) + outside * depth;
	
	normalVar = normalize(normal);
	
	vec3 u = normalize(modelviewMatrix * vector4(position, 1.0)).xyz;
	vec3 n = normalize(modelviewMatrix * vec4(normal, 1.0)).xyz;
	vec3 r = reflect( u, n );
	float m = 2.0 * sqrt( r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0) );
	
	texCoord0Var = vec2(r.x/m + 0.5, r.y/m + 0.5);
}

//[FRAG]
varying lowp vec4 colorVar;
varying lowp vec2 texCoord0Var;
varying lowp vec3 normalVar;

uniform sampler2D diffuseTex;

void main()
{
	lowp float d = 1.0/512.0;
	
	gl_FragColor = texture2D(diffuseTex, texCoord0Var);	
}
