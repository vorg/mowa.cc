//[VERT]
attribute vec3 position;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;


void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}

//[FRAG]

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	
}
