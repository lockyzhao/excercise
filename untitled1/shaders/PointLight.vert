//#version 330 core


uniform mat4 MVP;
uniform mat4 NormalMatrix;
uniform mat4 ModelViewMatrix;

varying vec3 normal;
varying vec4 pos;
//varying vec4 color;

attribute vec4 vert;
attribute vec3 normal0;

void main() {
  normal =normalize(ModelViewMatrix * vec4(normal0,0));
  gl_Position = MVP * vert;
  pos = ModelViewMatrix * vert;
  //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
