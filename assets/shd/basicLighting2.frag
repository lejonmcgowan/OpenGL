#version 330

struct PhongMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 speculuar;
    float speculuarExp;
};

in vec3 surfaceNormal;
in vec3 worldCoord;

uniform PhongMaterial material;
uniform PhongMaterial lightMaterial;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 lightDir = normalize(lightPos - worldCoord);
    vec3 viewDir   = normalize(viewPos - worldCoord);
    vec3 normalDir   = normalize(surfaceNormal);

    //calculate ambient
    vec3 ambient = lightMaterial.ambient * material.ambient;
    //calulate diffuse
    vec3 diffuse = lightMaterial.diffuse * material.diffuse *
    max(dot(lightDir,normalDir),0.0f);
    //calculate specular
    vec3 halfVector = normalize(lightPos + viewPos);
    vec3 specular = lightMaterial.speculuar * material.speculuar *
    pow(max(dot(viewDir,halfVector),0.0f),material.speculuarExp);


    //combine and send off
    gl_FragColor = vec4(ambient + diffuse + specular,1.0f);
}
