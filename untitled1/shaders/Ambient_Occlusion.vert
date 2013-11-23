attribute vec3 normal0;
attribute vec4 vert;

uniform float g_fScale;

varying vec2 g_vec2TexCoord0; 
varying vec3 g_vec3Normal; 
varying vec3 g_vec3Vertex;
varying vec3 normal;
void main() 
{ 
	//normal= gl_NormalMatrix * normal0;
    gl_Position =   gl_ModelViewProjectionMatrix * vert;    
 	g_vec2TexCoord0 = vec2(gl_MultiTexCoord0.s, 1.0 - gl_MultiTexCoord0.t); 
 	g_vec3Normal = vec3(normal0);

    g_vec3Vertex = vec3(vert); 
    
}