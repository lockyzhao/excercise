uniform sampler2D tex;
varying vec2 vs_tex_coord;

void main(void)
{
	gl_FragColor = texture2D(tex, vs_tex_coord);		
}