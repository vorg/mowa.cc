//[VERT]
//[VERT]
attribute vec2 position;
attribute vec2 texCoord0;
varying vec2 texCoord0Var;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);		
	texCoord0Var = texCoord0;
}

//[FRAG]
varying highp vec2 texCoord0Var;
uniform sampler2D tex0;

void main()
{
	gl_FragColor = texture2D(tex0, texCoord0Var);
}
