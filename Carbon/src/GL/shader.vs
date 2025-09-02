#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 a_uv;

out vec2 uv;

uniform mat4 pv; //projection*view

void main()
{
    uv = a_uv;
    gl_Position = pv*vec4(aPos, 1.0);
}