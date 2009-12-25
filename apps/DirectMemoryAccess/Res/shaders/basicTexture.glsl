//[VERT]
attribute vec4 position;


void main()
{
	gl_Position = projectionMatrix * modelviewMatrix * position;	
}

//[FRAG]
varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
