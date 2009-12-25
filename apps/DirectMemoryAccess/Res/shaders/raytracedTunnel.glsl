//[VERT]
attribute vec2 position;
attribute vec2 normal;
attribute vec2 texCoord0;
varying vec2 texCoord0Var;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);		
	texCoord0Var = position;
}

//[FRAG]
varying lowp vec2 texCoord0Var;
uniform sampler2D diffuseTex; 
uniform highp float time;

void main()
{
	highp vec2 p = texCoord0Var;

	highp vec2 uv;

	//twirl
	//highp float r = sqrt(p.x*p.x + p.y*p.y);
    //highp float x = p.x*cos(r)-p.y*sin(r);
    //highp float y = p.x*sin(r)+p.y*cos(r);
	//uv.x = 0.25 * x/abs(y);
    //uv.y = 0.520 * time + 0.25/abs(y);
	
	//flat tunnel
	//highp float an = 0.0;//time * 0.25;
	//highp float x = p.x*cos(an)-p.y*sin(an);
    //highp float y = p.x*sin(an)+p.y*cos(an);
	//uv.x = 0.25 * x/abs(y);
    //uv.y = 0.520 * time + 0.25/abs(y);

	highp float r = sqrt(p.x*p.x + p.y*p.y);
	highp float a = atan(p.y, p.x);
	highp float pi = 3.14159265;
	uv.x = 0.1/(r+0.5*p.x);
	uv.y = time*0.25+1.0*a/pi;

    gl_FragColor = texture2D(diffuseTex,uv) * r;//abs(p.y);
}

