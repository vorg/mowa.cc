//[VERT]
attribute vec3 position;
attribute vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelWorldMatrix;
uniform vec3 lightPos; //light pos in world coordinates
uniform vec3 lightPos2; //light pos in world coordinates
uniform vec3 cameraPos; //light pos in world coordinates

varying vec3 wN; //normal in world space
varying vec3 wL; //vector from position to light in world space
varying vec3 wL2; //vector from position to light in world space

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	
	vec3 wPos = vec3(modelWorldMatrix * vec4(position, 1.0));
	wN = vec3(modelWorldMatrix * vec4(normal, 1.0));
	wL = lightPos - wPos;
	wL2 = lightPos2 - wPos;	
}

//[FRAG]
varying vec3 wN; //normal in world space
varying vec3 wL; //vector from position to light in world space
varying vec3 wL2; //vector from position to light in world space

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 diffuseColor2;
uniform vec4 specularColor;

uniform vec3 cameraPos;

void main()
{
	float dist = length(wL) + 0.00001;
	float quadraticAttenuation = 0.5;
	float attenuation = 1.0 / (quadraticAttenuation * dist);
	vec3 N = normalize(wN);
	vec3 L = normalize(wL);
	float specular = 0.0;
	
	float NdotL = max(0.0, dot(N, L));
	if (NdotL != 0.0) {
		vec3 halfVector = normalize(normalize(cameraPos) + L);
		float NdotHV = max(0.0, dot(N, halfVector));
		float shininess = 128.0;
		specular = pow(NdotHV, shininess); 
	}
	gl_FragColor = ambientColor + diffuseColor * (NdotL * attenuation) + specularColor * (specular * attenuation);
	
	dist = length(wL2) + 0.00001;
	quadraticAttenuation = 0.5;
	attenuation = 1.0 / (quadraticAttenuation * dist);
	N = normalize(wN);
	L = normalize(wL2);
	specular = 0.0;
	
	NdotL = max(0.0, dot(N, L));
	if (NdotL != 0.0) {
		vec3 halfVector = normalize(normalize(cameraPos) + L);
		float NdotHV = max(0.0, dot(N, halfVector));
		float shininess = 128.0;
		specular = pow(NdotHV, shininess); 
	}
	gl_FragColor +=  diffuseColor2 * (NdotL * attenuation) + specularColor * (specular * attenuation);
	
}
