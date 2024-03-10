#version 410

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform bool is_rendering_enemy_tank;
uniform int shader_tank_hp;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;

float rand(vec3 coefficient);

void main()
{
    world_position = (Model * vec4(v_position, 1.0)).xyz;
    world_normal = normalize(mat3(Model) * v_normal);

    vec3 last_v_position = v_position;
    if (is_rendering_enemy_tank)
    {
        if (shader_tank_hp == 0)
        {
            gl_Position = Projection * View * Model * vec4(v_position, 1.0);
        }

        else if (shader_tank_hp == 1)
        {
            gl_Position = Projection * View * Model * vec4(last_v_position + int(pow(rand(v_position), shader_tank_hp)) * 0.0001, 1.0);
        }

        else if (shader_tank_hp == 2)
        {
            gl_Position = Projection * View * Model * vec4(last_v_position + int(pow(rand(v_position), shader_tank_hp)) * 0.0000002, 1.0);
        }

        else if (shader_tank_hp >= 3)
        {
            gl_Position = Projection * View * Model * vec4(last_v_position + int(pow(rand(v_position), shader_tank_hp)) * 0.0000000003, 1.0);
        }
    }
    else
    {
        gl_Position = Projection * View * Model * vec4(v_position, 1.0);
    }
}

float rand(vec3 x)
{
    return fract(sin(dot(x, vec3(12.9898, 78.233, 16.9239))) * 43758.5453) * 1000;
}
