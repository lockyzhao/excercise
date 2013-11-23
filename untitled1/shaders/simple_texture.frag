#version 330
#pragma debug(on)
uniform sampler2D tex;
#if __VERSION__>=130
in vec2 vs_tex_coord;
layout (location = 0) out vec4 color;
flat in int instanceID;
#else
varying vec2 vs_tex_coord;
varying vec4 color;
#endif
void main(void)
{
	color = texture(tex, vs_tex_coord);		
	if (instanceID==1) color=vec4(color.r,0,0,0);
	else{ color.r=0;color.a=0;}
}