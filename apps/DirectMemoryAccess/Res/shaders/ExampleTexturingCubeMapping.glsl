//CM - CubeMapping
//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 camPos;

varying vec3 reflectDir;
varying float lightIntensity;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);	
	vec3 N = normalize(vec3(modelViewMatrix * vec4(normal, 1.0)));
	vec4 ecPos = modelViewMatrix * vec4(position, 1.0);
	vec3 eyeDir = normalize(ecPos.xyz - camPos);
	reflectDir = reflect(eyeDir, normal);
	lightIntensity = max(dot(normalize(vec3(modelViewMatrix*vec4(camPos,1.0)) - eyeDir), normal), 0.0);
}

//[FRAG]
uniform samplerCube tex0;
varying highp vec3 reflectDir;
varying highp float lightIntensity;


void main()
{
	gl_FragColor = textureCube(tex0, reflectDir);	
	//gl_FragColor.rgb = reflectDir;
}
