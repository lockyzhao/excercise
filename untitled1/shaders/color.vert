varying vec3 pos;
void main() {	
    pos = (gl_Vertex.zyx);    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position=ftransform()
}