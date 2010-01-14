//[VERT]
attribute vec3 position;
attribute vec3 normal;

varying vec3 texCoord0Var;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);		
	texCoord0Var = normalize(normal);
}


//[FRAG]
varying highp vec3 texCoord0Var;
uniform samplerCube tex0;

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0) + textureCube(tex0, texCoord0Var);	
}
