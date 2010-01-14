//[VERT]
attribute vec3 position;
attribute vec2 texCoord0;
attribute vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

varying vec3 normalVar;
varying vec3 posVar;
varying vec3 ecPosVar;
varying vec2 texCoord0Var;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	vec4 ecPos = modelViewMatrix * vec4(position, 1.0);
	normalVar = normal;
	posVar = position;
	ecPosVar = ecPos.xyz;
	texCoord0Var = texCoord0;
}

//[FRAG]

varying vec3 normalVar;
varying vec3 posVar;
varying vec3 ecPosVar;
varying vec2 texCoord0Var;

uniform sampler2D tex0;
uniform float time;

float minz = 0.0;
float maxz = -100.0;

void main()
{
	//gl_FragColor.rgb = normalVar;
	//return;
	
	vec3 diffuseColor = vec3(0.5) + 0.5*normalize(normalVar);
	vec3 fogColor = vec3(217.0/256.0, 186.0/256.0, 167.0/256.);
	//gl_FragColor.rgb = mix(fogColor, diffuseColor, (zVar-minz)/(maxz-minz));
	//gl_FragColor.rgb = vec3(abs(posVar.x)/10.0);
	//vec3 fog = max(vec3(abs(posVar.x)/10.0), vec3(-posVar.z/20.0));
	float fogDist = length(vec3(ecPosVar.x, ecPosVar.y, ecPosVar.z/2.0)*mix(0.08, 0.85, time/50.0));//20
	fogDist = fogDist*fogDist;
	float y = (ecPosVar.y + 3.0)/6.0;
	if (y < 0.2 || y > 0.8) {
		diffuseColor = mix(vec3(58.0/456.0, 36.0/456.0, 30.0/456.0), vec3(192.0/256.0, 169.0/256.0, 126.0/256.0), y); 
	}
	else {
		diffuseColor = mix(vec3(58.0/256.0, 36.0/256.0, 30.0/256.0), vec3(172.0/256.0, 149.0/256.0, 106.0/256.0), y); 
	}
	gl_FragColor.rgb = mix(diffuseColor, fogColor, fogDist);
	gl_FragColor.rgb *= 0.8+0.2*dot(normalize(normalVar), normalize(vec3(0.0, 0.0, -1.0)));
	gl_FragColor.rgb += vec3(texture2D(tex0, texCoord0Var).r*0.4);
	gl_FragColor.rgb *= gl_FragColor.rgb;
	
	//gl_FragColor.rgb = vec3(fogDist);
}
