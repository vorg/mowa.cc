//[VERT]
attribute vec3 position;
attribute vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

varying vec3 ecN; //normal in eye space
varying vec3 ecL; //vector from position to light in eye space
varying vec3 ecPos;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	
	vec4 ecPos4 = modelViewMatrix * vec4(position, 1.0);
	ecPos = vec3(modelViewMatrix * vec4(position, 1.0));//correct would be ecPos4.xyz/ecPos4.w;
	ecN = vec3(modelViewMatrix * vec4(normal, 1.0));
	//ecN = normal;
	//ecL = ecLightPos - ecPos;
	//ecL = vec3(0.0, 0.0, -10.0) - ecPos;
	//ecL = ecPos;
	//ecL = normalize(vec3(0, 0, 5) - ecPos);
}

//[FRAG]
varying vec3 ecN; //normal in eye space
//varying vec3 ecL; //vector from position to light in eye space
varying vec3 ecPos;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform vec3 ecLightPos; //light pos in eye coordinates

void main()
{
	vec3 ecCameraPos = vec3(0.0, 0.0, 0.0); //light pos in eye coordinates
	vec3 ecL = vec3(0.0);//ecLightPos - ecPos;
	float dist = length(ecL) + 0.00001;
	float quadraticAttenuation = 1.0;
	float attenuation = 1.0;//1.0 / (quadraticAttenuation * dist);
	//vec3 N = normalize(ecN);
	//vec3 L = normalize(ecL);
	
	vec3 N = normalize(vec3(0.0, 0.0, 1.0));
	vec3 L = normalize(vec3(0.0, 0.0, 1.0));
	float NdotL = max(0.0, dot(N, L));
	gl_FragColor = ambientColor + diffuseColor * (NdotL * attenuation);
	//gl_FragColor.rgb = vec3(0.5) + 0.5*vec3(L);//ambientColor + diffuseColor * (NdotL * attenuation);
}
