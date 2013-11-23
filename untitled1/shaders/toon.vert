varying vec3 normal;
uniform mat4 mvp_matrix;
//varing vec3 vertex
void main() {
    normal = gl_NormalMatrix * gl_Normal;
    gl_Position = mvp_matrix * gl_Vertex;
}
