//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform float time;
uniform float strength;

varying vec2 texCoord0Var;
varying vec3 normalVar;

float PI = 3.14159265358979323846264;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	texCoord0Var = texCoord0;	
	normalVar = normal;
}

//[FRAG]
varying highp vec2 texCoord0Var;
varying highp vec3 normalVar;
uniform sampler2D tex0;

void main()
{
	//gl_FragColor = vec4(texCoord0Var, 1.0, 1.0) * texture2D(tex0, texCoord0Var);	
	gl_FragColor = texture2D(tex0, texCoord0Var);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
