//[VERT]
attribute vec3 position;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

varying vec2 texCoord0Var;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	texCoord0Var = texCoord0;	
}

//[FRAG]
varying highp vec2 texCoord0Var;
uniform sampler2D tex0;

void main()
{
	gl_FragColor = texture2D(tex0, texCoord0Var);
}
