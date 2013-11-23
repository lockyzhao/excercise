attribute vec4 vert;
attribute vec3 normal0;
varying vec3 normal;

void main() {
    //normal = gl_NormalMatrix * gl_Normal;
    normal= gl_NormalMatrix * normal0;
    gl_Position = gl_ModelViewProjectionMatrix * vert;
}