// Fragment Shader
#version 410 core
precision highp float;
uniform sampler2D u_texture;
uniform int u_mode_f;
uniform vec3 u_color;
uniform vec3 u_light_d;
in vec2 p_texcoord;
in vec3 p_normal;
out vec4 o_color;

void main() {
    if (u_mode_f == 0 || u_mode_f == 2) {
        o_color = texture(u_texture, p_texcoord);
    } else if (u_mode_f == 1) {
        o_color = vec4(u_color, 1.0);
    } else if (u_mode_f == 3) {
        float brightness = max(dot(p_normal, normalize(-u_light_d)), 0.2);
        o_color = vec4(u_color.x * brightness, u_color.y * brightness, u_color.z * brightness, 1.0);
    } else if (u_mode_f == 4) {
        vec4 color = texture(u_texture, p_texcoord);
        float brightness = max(dot(p_normal, normalize(-u_light_d)), 0.2);
        o_color = vec4(color.x * brightness, color.y * brightness, color.z * brightness, color.w);
    }
}