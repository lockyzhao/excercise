#version 330
#if __VERSION__>=130
	layout (location = 0) in vec4 vert;
	layout (location = 1) in vec3 normal0;
	layout (location = 2) in vec2 tex_coord;
	layout (location = 3) uniform int instID0;
	out vec2 vs_tex_coord,normal;	
	flat out int instanceID;
#else
	attribute vec4 vert;
	attribute vec3 normal0
	attribute vec2 tex_coord;
	varying vec2 vs_tex_coord;
#endif

void main(void)
{

	gl_Position = gl_ModelViewProjectionMatrix * vert;		
	vs_tex_coord = tex_coord;	
	instanceID=instID0;
	//vs_tex_coord=gl_MultiTexCoord0.st;
	
}
