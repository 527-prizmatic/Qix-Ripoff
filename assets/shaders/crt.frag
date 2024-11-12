uniform vec2 uRes;
uniform float uTime;
uniform vec2 uZoom;
uniform sampler2D texture;

float harmonics(float _a, float _harm) {
	return sin(_a * 3.1415 * _harm) / pow(3., _harm - 1);
}

float harmonics_sum(float _a, float _harmonics) {
	float sum = 0.;
	for (float i = 0.; i < _harmonics; i += 1.) {
		sum += harmonics(_a, i * 2. + 1.);
	}

	return sum;
}

void main() {
	vec2 uv = (gl_FragCoord / uRes);
	vec2 uvScaled = uv * uZoom;

	vec2 px = gl_TexCoord[0].xy;
	vec2 dist = vec2(0., 0.);
	
	dist.x = .1 * (.5 - uvScaled.x) * harmonics_sum(uvScaled.y, 4.);
	dist.y = -.1 * (.5 - uvScaled.y) * harmonics_sum(uvScaled.x, 4.);
	px += dist;
	px.y = 1. - px.y;

	vec2 pxZoomOut = px * 1.2 - vec2(.1);
	vec4 clr = vec4(0., 0., 0., 1.);
	if (pxZoomOut.x >= 0. && pxZoomOut.y >= 0. && pxZoomOut.x <= 1. && pxZoomOut.y <= 1.) {
		clr = texture2D(texture, px * 1.2 - vec2(.1));

		float scanline = clamp(sin(px.y * 750. + uTime * 4.) * 10 + .5, 0., 1.);
		clr.r += .005;
		clr.g += .01;
		clr.b += .02;
		clr.r *= 1. - .25 * scanline;
		clr.g *= 1. + .125 * scanline;
		clr.b *= 1. + scanline;
	}
	
	gl_FragColor = clr;
}