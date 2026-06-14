#version 330 core

in vec3 colorVS;
in vec3 normalVS;
in vec3 lightDirVS;
in vec3 viewDirVS;

uniform vec3 lightColor;

out vec4 color;

void main(){
    // Normalize necessary vectors
    vec3 N = normalize(normalVS);
    vec3 L = normalize(lightDirVS);
    vec3 V = normalize(viewDirVS);
    
    // Diffuse component
    float cosA = max(0.0, dot(N, L));
    vec3 diffuseTerm = colorVS * lightColor * cosA;
    
    // Specular component
    vec3 R = normalize(reflect(-L, N));
    float cosBeta = max(0.0, dot(R, V));
    float cosBetaShininess = pow(cosBeta, 32.0);  // 32.0 is shininess factor
    vec3 specularTerm = vec3(1.0) * lightColor * cosBetaShininess;  // white specular highlights
    
    color = vec4(diffuseTerm + specularTerm, 1.0);
}

