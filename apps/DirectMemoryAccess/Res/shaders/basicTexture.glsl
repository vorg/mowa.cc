//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform float time;
uniform float strength;

varying vec2 texCoord0Var;
float PI = 3.14159265358979323846264;

void main()
{
	vec4 pos = normalize(vec4(position, 1.0));
	pos.xyz +=  strength*0.1 * sin(time*-5.0 + texCoord0.t * 4.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 4.0 * PI) * normal;
	float minLen = 1.0 - strength*0.3;
	float maxLen = 1.0 + strength*0.3;
	gl_Position = projectionMatrix * modelViewMatrix * pos;

	texCoord0Var = texCoord0;	
}

//[FRAG]
varying lowp vec2 texCoord0Var;
uniform sampler2D tex0;

void main()
{
	gl_FragColor = texture2D(tex0, texCoord0Var);	
}
