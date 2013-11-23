//#version 330 core


uniform mat4 MVP;
uniform mat4 NormalMatrix;
uniform mat4 ModelViewMatrix;

out vec3 normal;
out vec4 pos;
//varying vec4 color;

in vec4 vert;
in vec3 normal0;

void main() {
  normal =normalize(ModelViewMatrix * vec4(normal0,0));
  gl_Position = MVP * vert;
  pos = ModelViewMatrix * vert;
  //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
