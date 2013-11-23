#version 330
#if __VERSION__<130
varying vec3 normal;
varying vec4 pos;
varying vec4 rawpos;
attribute vec4 vert;
attribute vec3 normal0;
#else
uniform int instID0;
out vec3 normal;
out vec4 pos;
out vec4 rawpos;
flat out int instanceID;
layout (location=0) in vec4 vert;
layout (location=1) in vec3 normal0;
#endif
void main() {
  normal = gl_NormalMatrix * normal0;
  gl_Position = gl_ModelViewProjectionMatrix * vert;
  pos = gl_ModelViewMatrix * vert;
  rawpos = vert;
  instanceID=instID0;
  //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}