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
varying vec3 positionVar;
varying vec3 normalVar;
float PI = 3.14159265358979323846264;

mat3 getLinearPart(mat4 m)
{
	mat3 result;
	
	result[0][0] = m[0][0]; 
	result[0][1] = m[0][1]; 
	result[0][2] = m[0][2]; 

	result[1][0] = m[1][0]; 
	result[1][1] = m[1][1]; 
	result[1][2] = m[1][2]; 
	
	result[2][0] = m[2][0]; 
	result[2][1] = m[2][1]; 
	result[2][2] = m[2][2]; 
	
	return result;
}

void main()
{
	mat3 modelWorld3x3 = getLinearPart(modelWorldMatrix);
	vec4 pos = normalize(vec4(position, 1.0));
	gl_Position = projectionMatrix * modelViewMatrix * pos;
	vec3 worldPos =  modelWorld3x3 * position;
	vec3 N = normalize(modelWorld3x3 * normal);
	vec3 E = normalize(worldPos - camPos);
	reflectDir = reflect(E, N);	
	positionVar = pos.xyz;
	normalVar = normal;
}

//[FRAG]
varying vec3 reflectDir;
varying vec3 positionVar;
varying vec3 normalVar;
uniform samplerCube tex0;

void main()
{
	if (length(positionVar.xyz) < 0.5) {
		discard;
	}
	else {
		gl_FragColor = (vec4(0.2) + textureCube(tex0, reflectDir)*textureCube(tex0, reflectDir)) * (abs(normalVar.x));	
	}
}
