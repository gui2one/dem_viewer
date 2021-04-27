#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 t_coords;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_coords;
void main(){

    f_position = vec3(u_model * vec4(position, 1.0));
    f_normal = inverse(transpose(mat3(u_model))) * -normal;
    f_coords = t_coords;
    gl_Position = u_projection * u_view  * vec4(f_position,1.0);
}