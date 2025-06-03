#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 0) out vec3 out_color;


vec3 triangle_colors[6] = vec3[](
vec3(1.0, 0.3, 0.3),  // Rosso acceso
vec3(1.0, 0.9, 0.2),  // Giallo intenso
vec3(0.4, 1.0, 0.4),  // Verde brillante
vec3(0.3, 0.6, 1.0),  // Azzurro intenso
vec3(0.6, 0.3, 1.0),  // Viola acceso
vec3(1.0, 0.4, 0.7)   // Rosa acceso

);

layout(push_constant) uniform PushConstants 
{
    mat4 viewProjection;
    mat4 Transform;
} u_PushConstants;

void main()
{
    gl_Position = u_PushConstants.viewProjection * u_PushConstants.Transform * vec4(a_Position, 1.0);

    out_color = triangle_colors[gl_VertexIndex % 6];
}
