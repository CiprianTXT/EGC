#version 410

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform bool is_rendering_enemy_tank;
uniform int shader_tank_hp;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_position);

void main()
{
    vec3 damage_color = vec3(1);
    if (is_rendering_enemy_tank)
    {
        damage_color = vec3(pow(1.5, shader_tank_hp));
    }

    float ambient_light = 0.5;

    float light = ambient_light + point_light_contribution(light_position);

    out_color = vec4(object_color / damage_color * light, 1);
}

float point_light_contribution(vec3 light_position)
{
    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);

    float ambient_light = 0.5;
    float diffuse_light = material_kd * max(dot(N, L), 0);
    float specular_light = 0;

    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
    }

    float distance = distance(light_position, world_position);

    return diffuse_light + specular_light;
}
