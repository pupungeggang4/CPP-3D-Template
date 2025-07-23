#version 410 core
uniform int u_mode_v;
in vec4 a_position;

void main() {
    gl_Position = a_position;
}