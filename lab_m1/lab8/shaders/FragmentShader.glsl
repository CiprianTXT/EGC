#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_position1;
uniform vec3 light_position2;
uniform vec3 light_direction;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform bool is_spotlight;
uniform vec3 object_color;
uniform float cut_off;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_position);

void main()
{
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    float ambient_light = 0.25;
    
    float light = ambient_light + point_light_contribution(light_position1) + point_light_contribution(light_position2);

    // TODO(student): Write pixel out color
    out_color = vec4(object_color * light, 1);
}

float point_light_contribution(vec3 light_position)
{
    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);

    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = material_kd * max(dot(N, L), 0);
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.    
    float spot_light_att_factor = 1;
    if (is_spotlight)
    {
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);

        if (spot_light > spot_light_limit)
        {
            // Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            spot_light_att_factor = pow(linear_att, 2);
        }
        else
        {
            return 0;
        }
    }
    float distance = distance(light_position, world_position);
    float light_att_factor = 1 / (1 + 0.12 * distance + 0.05 * distance * distance);
    
    return light_att_factor * spot_light_att_factor * (diffuse_light + specular_light);
}
