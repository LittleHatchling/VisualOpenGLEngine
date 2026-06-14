#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colorRGB;

out vec3 colorVS;
out vec3 normalVS;
out vec3 lightDirVS;
out vec3 viewDirVS;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    colorVS = colorRGB;
    
    // Transform normal to view space
    vec4 n = vec4(normal, 0.0);
    mat4 normalMat = transpose(inverse(viewMatrix * transformMatrix));
    normalVS = (normalMat * n).xyz;
    
    // Transform vertex position to view space
    vec4 P = viewMatrix * transformMatrix * vec4(pos, 1.0);
    
    // Transform light position to view space and compute light direction
    vec4 lp = viewMatrix * vec4(lightPosition, 1.0);
    lightDirVS = (lp - P).xyz;
    
    // View direction (camera is at origin in view space, so it's negative of position)
    viewDirVS = -P.xyz;
    
    gl_Position = projectionMatrix * P;
}