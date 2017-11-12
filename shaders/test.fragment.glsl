//varying vec2 coordinate;

uniform sampler2D texture;

void main(void) {
  vec4 color = texture2D(texture, gl_FragCoord);
  vec4 black = vec4(.0, .0, .0, 1.);
  gl_FragColor = mix(color, black, .5);
}
