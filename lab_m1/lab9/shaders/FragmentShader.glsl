#version 410

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;

// TODO(student): Declare various other uniforms
uniform double elapsedTime;
uniform bool isEarth;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec4 color_texture_1, color_texture_2;
    if (isEarth)
    {
        color_texture_1 = texture2D(texture_1, texcoord + vec2(elapsedTime, 0));
    }
    else
    {
        color_texture_1 = texture2D(texture_1, texcoord);
    }
    if (color_texture_1[3] < 0.5f)
    {
        discard;
    }
    
    if (isEarth)
    {
        color_texture_2 = texture2D(texture_2, texcoord + vec2(elapsedTime, 0));
    }
    else
    {
        color_texture_2 = texture2D(texture_2, texcoord);
    }
    if (color_texture_2[3] < 0.5f)
    {
        discard;
    }
    out_color = mix(color_texture_1, color_texture_2, 0.3f);
}
