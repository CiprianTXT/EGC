#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec2 texcoord;

uniform bool isGrass;

void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;
    
    vec4 v_pos = vec4(v_position, 1.0);
    vec3 v_dir = normalize(vec3(-View[0][2], 0, -View[2][2]));
    if (isGrass)
    {
        vec3 right = normalize(cross(vec3(0, 1, 0), v_dir));
        vec3 up = cross(v_dir, right);
        
        mat4 billboardView = mat4(
            right.x, up.x, -v_dir.x, 0,
            right.y, up.y, -v_dir.y, 0,
            right.z, up.z, -v_dir.z, 0,
            0, 0, 0, 1
        );
        
        v_pos = billboardView * v_pos;
    }
    
    gl_Position = Projection * View * Model * v_pos;
}
