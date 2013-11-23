uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 lightPosition;
//uniform vec3 lightDirection;  //direction toward light
//uniform vec3 halfVector;    //surface orientation for shiness spot

uniform float shininess; // exponent for sharping high lights
uniform float strength; //extract to adjust the shiness.

uniform vec3 eyeDirection;
uniform float constantAttenuation; //attenuation coefficients
uniform float linearAttenuation;
uniform float QuadraticAttenuation;

in vec3 normal;
in vec4 pos;
//varying vec4 color;

void main() {
    vec4 color=vec4(1,1,1,0);

    vec3 lightDirection=lightPosition -vec3(pos);
    float lightDistance=length(lightDirection);

    // normalize the light direction vector
    lightDirection=lightDirection / lightDistance;


    // model how much light is available for this fragment
//    float attenuation =1.0/(constantAttenuation+
//                            linearAttenuation*lightDistance+
//                            QuadraticAttenuation*lightDistance*lightDistance);
    float attenuation=1.0;

    vec3 halfVector= normalize(lightDirection+eyeDirection);

    float diffuse = max(0.0, dot(normal,lightDirection));
    float specular= max(0.0, dot(normal,halfVector));

    if(diffuse==0.0) specular=0.0;
    else
        specular=pow(specular, shininess);

    vec3 scatteredLight= ambient+ lightColor* diffuse* attenuation;
    vec3 reflectLight= lightColor* specular* strength;

    vec3 rgb= min(color.rgb*scatteredLight+reflectLight, vec3(1.0));
    gl_FragColor=vec4(rgb,color.a);


}
