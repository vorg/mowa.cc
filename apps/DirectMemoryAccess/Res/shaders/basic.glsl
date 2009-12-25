//[VERT]
attribute vec4 position;
attribute vec4 color;

varying vec4 colorVarying;

uniform float time;

void main()
{
	gl_Position = position;
	gl_Position.y += sin(time) / 2.0;
	
	colorVarying = color;
}

//[FRAG]
varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
