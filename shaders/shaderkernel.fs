#version 330
const float offset = 1.0 / 300;  
in vec2 TexCoord;
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
out vec4 FragColor;
void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right
    );

    float kernel[9] = float[](
      1.0 / 16, 2.0 / 16, 1.0 / 16,
      2.0 / 16, 4.0 / 16, 2.0 / 16,
      1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        vec2 z = vec2(TexCoord.x,1.0 - TexCoord.y);
        sampleTex[i] = vec3(texture(diffuse_texture, z.st + offsets[i]));
    }
    vec3 col;
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
//    vec2 z = vec2(TexCoord.x,1.0 - TexCoord.y);
    FragColor =vec4(col, 1.0);//texture(diffuse_texture,z);// 
}