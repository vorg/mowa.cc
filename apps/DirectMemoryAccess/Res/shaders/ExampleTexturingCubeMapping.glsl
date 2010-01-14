//CM - CubeMapping
//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelWorldMatrix;
uniform vec3 camPos;
uniform float skybox;
uniform float scale;

varying vec3 reflectDir;
varying vec2 texCoord0Var;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position * scale, 1.0);	
	if (skybox == 0.0) {
		vec3 worldPos = vec3(modelWorldMatrix * vec4(position * scale, 1.0));
		vec3 N = vec3(modelWorldMatrix * vec4(normal, 1.0));
		vec3 E = normalize(worldPos - camPos);
		reflectDir = reflect(E, N);				
	}
	else {
		reflectDir = normal;
	}
	texCoord0Var = texCoord0;
	//texCoord0Var = vec2(0.0, 0.0);
}

//[FRAG]
uniform samplerCube tex0;
uniform sampler2D tex1;
varying highp vec3 reflectDir;
varying highp vec2 texCoord0Var;

void main()
{
	gl_FragColor = vec4(0.1) + 1.0 * textureCube(tex0, reflectDir) + 0.0 * texture2D(tex1, texCoord0Var);	
	gl_FragColor *= gl_FragColor;
	
}
