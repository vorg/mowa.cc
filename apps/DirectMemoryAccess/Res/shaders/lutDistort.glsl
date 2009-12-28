//[VERT]
attribute vec2 position;
attribute vec2 normal;
attribute vec2 texCoord0;
varying vec2 texCoord0Var;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);		
	texCoord0Var = position;
}

//[FRAG]
varying lowp vec2 texCoord0Var;
uniform sampler2D diffuseTex; 
uniform highp float time;
uniform highp float mode;
uniform highp float crossFade;

void main()
{
	highp float x = texCoord0Var.x;
	highp float y = texCoord0Var.y;
	
	highp float d = sqrt(x*x + y*y);
	highp float a = atan(y, x);
	
	highp float PI = 3.14159265358979323846264;
	highp float t = time * 0.75;
	
	highp float u;
	highp float v;
	
	highp float fog = d;
        
	if (mode < 1.0) {
		//forward tunnel	
		u = 0.3/(d+0.2*x);
		v = 3.0*a/PI;
		
		//highp float shift = crossFade;
//		highp float d2 = sqrt((x-shift)*(x-shift) + (y-0.0)*(y-0.0));
//		highp float a2 = atan(y - 0.0, x - shift);
//		highp float u2 = 0.3/(d2+0.5*(x-shift));
//		highp float v2 = 3.0*a2/PI;
//		highp float fog2 = d2;
//		
//		gl_FragColor = texture2D(diffuseTex, vec2(u,v) + vec2(t)) * fog;
//		gl_FragColor += texture2D(diffuseTex, vec2(u2,v2) + vec2(t)) * fog2;	
//		gl_FragColor *= 0.5;
		
		//u = (1.0 - crossFade) * u + crossFade * u2;
		//v = (1.0 - crossFade) * v + crossFade * v2;		
		//fog = (1.0 - crossFade) * d + crossFade * d2;

	}
	else if (mode < 2.0) {
		//plasma in/out tunnel, time/2
		u = 0.02*y+0.03*cos(a*3.0)/d;
		v = 0.02*x+0.03*sin(a*3.0)/d;
		t *= 0.1;
	}
	else if (mode < 3.0) {
		//spiral tunnel
		u = cos(a)/d;
		v = sin(a)/d;
		t *= 1.5;
	}
	else if (mode < 4.0) {
		//warmhole
		u = x*cos(2.0*d) - y*sin(2.0*d);
		v = y*cos(2.0*d) + x*sin(2.0*d);
	}
	else if (mode < 5.0) {
		//right to left light beams
		u = 0.1*x/(0.11+d*0.5);
		v = 0.1*y/(0.11+d*0.5);
		t = time * 0.2;
	}
	else if (mode < 6.0) {
		//rotating pool plasma
		u = 0.5*a/PI;
		v = sin(7.0*d);
		t *= 0.2;
	}
	else if (mode < 7.0) {
		//backward twirl
		u = d*cos(a+d);
		v = d*sin(a+d);
	}
	else if (mode < 8.0) {
		//flower
		u = 1.0/(d+0.5+0.5*sin(5.0*a));
		v = a*3.0/PI;
		t *= 0.5;
	}
	else if (mode < 9.0) {
		//flat tunnel, abs(y)
		//u = x/abs(y);
		//v = 1.0/abs(y);
		u = 0.1/(d + 0.5*x);
		v = a/PI;
				
		highp float r = 0.0;
		highp float x2 = x*cos(r)-y*sin(r);
		highp float y2 = x*sin(r)+y*cos(r);
		u = 0.25 * x2/abs(y2);
		v = 0.220 * time + 0.25/abs(y2);
		fog = abs(y2);
		t = 0.0;
	}
	
	gl_FragColor = texture2D(diffuseTex, vec2(u,v) + vec2(t)) * fog * fog;	
}

