//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelWorldMatrix;
uniform vec3 camPos;

uniform float time;
uniform float strength;

varying vec3 reflectDir;
float PI = 3.14159265358979323846264;

void main()
{
	vec4 pos = normalize(vec4(position, 1.0));
	gl_Position = projectionMatrix * modelViewMatrix * pos;
	vec3 worldPos = vec3(modelWorldMatrix * vec4(position, 1.0));
	vec3 N = vec3(modelWorldMatrix * vec4(normal, 1.0));
	vec3 E = normalize(worldPos - camPos);
	reflectDir = reflect(E, N);	
}

//[FRAG]
varying highp vec3 reflectDir;
uniform samplerCube tex0;

void main()
{
	gl_FragColor = textureCube(tex0, reflectDir);	
}
