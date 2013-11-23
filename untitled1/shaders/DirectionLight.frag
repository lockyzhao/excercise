uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 lightDirection;  //direction toward light
uniform vec3 halfVector;    //surface orientation for shiness spot
uniform float shininess; // exponent for sharping high lights
uniform float strength; //extract to adjust the shiness.
varying vec3 normal;
varying vec4 pos;
//varying vec4 color;

void main() {
    vec4 color=vec4(1,1,1,0.);
    float diffuse = max(0.0, dot(normal,lightDirection));
    float specular= max(0.0, dot(normal,halfVector));

    if(diffuse==0.0) specular=0.0;
    else
        specular=pow(specular, shininess);

    vec3 scatteredLight= ambient+ lightColor* diffuse;
    vec3 reflectLight= lightColor* specular* strength;

    vec3 rgb= min(color.rgb*scatteredLight+reflectLight, vec3(1.0));
    gl_FragColor=vec4(rgb,color.a);


}
