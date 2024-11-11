uniform vec2 uRes;
uniform float uTime;
uniform vec2 uZoom;
uniform sampler2D texture;

float clamp(float _a, float _l, float _u) {
	if (_a < _l) return _l;
	else if (_a > _u) return _u;
	else return _a;
}

float pow4(float _a) {
	return _a * _a * _a * _a;
}

void main() {
	vec2 uv = (gl_FragCoord / uRes);

	vec2 px = gl_TexCoord[0].xy;
	vec2 dist = vec2(0., 0.);

	dist.x = (sin(uv.y * uZoom.y * 3.14) * (.5 - uv.x * uZoom.x)) * .025;
	dist.y = (sin(uv.x * uZoom.x * 3.14) * (.5 - uv.y * uZoom.y)) * .025;
	px += dist;

//	:trolle:
//	px.x += sin(uTime * 3. + uv.x * 5.) * .001;
//	px.y += sin(uTime * 3. + uv.y * 5.) * .001;

	vec4 clr = texture2D(texture, px);
	float scanline = clamp(sin(px.y * 3000. + uTime * 4.) * .5 + .25, 0., 1.);
	clr.r += .005;
	clr.g += .01;
	clr.b += .02;
	clr.r *= 1. - .25 * scanline;
	clr.g *= 1. + .125 * scanline;
	clr.b *= 1. + scanline;
	
	gl_FragColor = clr;
}