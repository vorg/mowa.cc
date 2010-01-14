//[VERT]
attribute vec3 position;
attribute vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelWorldMatrix;
uniform vec3 lightPos; //light pos in world coordinates

varying vec3 wN; //normal in world space
varying vec3 wL; //vector from position to light in world space

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	
	vec3 wPos = vec3(modelWorldMatrix * vec4(position, 1.0));
	wN = vec3(modelWorldMatrix * vec4(normal, 1.0));
	wL = lightPos - wPos;
}

//[FRAG]
varying vec3 wN; //normal in eye space
varying vec3 wL; //vector from position to light in eye space


void main()
{
	
	vec3 N = normalize(wN);
	vec3 L = normalize(wL);
	float NdotL = dot(N, L);
	if (NdotL < 0.0) {
		NdotL = 0.0;
	}
	gl_FragColor.rgb = vec3(NdotL);
}
