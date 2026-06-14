#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colorRGB;

out vec3 colorVS;
out vec3 normalVS;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    colorVS = colorRGB;
    normalVS = normal;
    gl_Position = projectionMatrix * viewMatrix * transformMatrix * vec4(pos, 1.0);
}