#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    colorVS = colorRGB;
    gl_Position = projectionMatrix * viewMatrix * transformMatrix * vec4(pos, 1.0);
}