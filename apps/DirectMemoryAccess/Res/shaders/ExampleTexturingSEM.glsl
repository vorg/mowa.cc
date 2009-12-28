//SEM - SphericalEnvironmentMapping
//[VERT]
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform float time;
uniform float strength;

varying vec2 texCoord0Var;

float PI = 3.14159265358979323846264;

void main()
{
	vec4 pos = vec4(position + normal*strength*0.2, 1.0);
	//pos.xyz +=  strength*0.1 * sin(time*-5.0 + texCoord0.t * 4.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 4.0 * PI) * normal;
	vec4 norm = normalize(vec4(normal, 1.0));
	//norm.xyz += strength*0.1 * sin(time*-5.0 + texCoord0.t * 4.0 * PI) * normal + strength*0.2 * sin(texCoord0.s * 4.0 * PI) * normal;
	float minLen = 1.0 - strength*0.3;
	float maxLen = 1.0 + strength*0.3;
	gl_Position = projectionMatrix * modelViewMatrix * pos;
	
	vec3 u = vec3(modelViewMatrix * pos);	 //normalize
	vec3 n = vec3(modelViewMatrix * norm);	 //normalize
	vec3 r = reflect( u, n );
	//float m = 2.0 * sqrt( r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0) ); //if normalized, but doesn't work
	float m = sqrt(r.x*r.x + r.y*r.y + r.z*r.z); 

	texCoord0Var = vec2(r.x/m + 0.5, r.y/m + 0.5);	
}

//[FRAG]
uniform sampler2D tex0;
uniform samplerCube cubeMap;

varying lowp vec2 texCoord0Var;

void main()
{
	gl_FragColor = texture2D(tex0, texCoord0Var);	
}
