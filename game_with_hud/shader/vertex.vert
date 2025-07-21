// Vertex Shader
#version 410 core
uniform int u_mode_v;
uniform vec3 u_m_pos;
uniform vec3 u_m_size;
uniform vec3 u_m_rot;
uniform vec3 u_c_pos;
uniform vec3 u_c_rot;
uniform vec4 u_c_proj;
in vec4 a_position;
in vec2 a_texcoord;
in vec3 a_normal;
out vec2 p_texcoord;
out vec3 p_normal;

void main() {
    if (u_mode_v == 0) {
        gl_Position = a_position;
        p_normal = vec3(-1.0, 0.0, 0.0);
    } else {
        mat4 m_m_pos = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            u_m_pos.x, u_m_pos.y, u_m_pos.z, 1.0
        );
        mat4 m_m_size = mat4(
            u_m_size.x, 0.0, 0.0, 0.0,
            0.0, u_m_size.y, 0.0, 0.0,
            0.0, 0.0, u_m_size.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_x = mat4(
            1.0, 0.0, 0.0, 0.0, 
            0.0, cos(u_m_rot.x), sin(u_m_rot.x), 0.0,
            0.0, -sin(u_m_rot.x), cos(u_m_rot.x), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_y = mat4(
            cos(u_m_rot.y), 0.0, -sin(u_m_rot.y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(u_m_rot.y), 0.0, cos(u_m_rot.y), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_z = mat4(
            cos(u_m_rot.z), -sin(u_m_rot.z), 0.0, 0.0,
            sin(u_m_rot.z), cos(u_m_rot.z), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_c_pos = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            u_c_pos.x, u_c_pos.y, u_c_pos.z, 1.0
        );
        mat4 m_z_inv = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, -1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        float fov = u_c_proj[0];
        float asp = u_c_proj[1];
        float near = u_c_proj[2];
        float far = u_c_proj[3];
        mat4 m_c_proj = mat4(
            1.0 / (asp * tan(fov / 2.0)), 0.0, 0.0, 0.0,
            0.0, 1 / tan(fov / 2.0), 0.0, 0.0,
            0.0, 0.0, -(far + near) / (far - near), -1.0,
            0.0, 0.0, -(2.0 * far * near) / (far - near), 0.0
        );
        vec4 pos = a_position;
        pos = m_m_pos * m_m_rot_z * m_m_rot_y * m_m_rot_x * m_m_size * pos;
        pos = m_z_inv * pos;
        pos = m_c_pos * pos;
        pos = m_c_proj * pos;
        gl_Position = pos;
        vec4 normal = vec4(normalize(a_normal), 1.0);
        normal = m_m_rot_z * m_m_rot_y * m_m_rot_x * normal;
        p_normal = normalize(vec3(normal.x, normal.y, normal.z));
    }
    p_texcoord = a_texcoord;
}