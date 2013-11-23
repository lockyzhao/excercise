attribute vec4 vert;
attribute vec3 normal0;
attribute vec2 tex_coord;
varying vec2 vs_tex_coord;


void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * vert;	
	vs_tex_coord = tex_coord;	
	//vs_tex_coord=gl_MultiTexCoord0.st;
	
}
