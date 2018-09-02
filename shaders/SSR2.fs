#version 330
in vec2 texcoord;
uniform sampler2D convolutional_image;
uniform sampler2D original_image;
out vec4 FragColor;
void main()
{


    vec2 reversed_texcoord = vec2(texcoord.x,1.0 - texcoord.y);
    FragColor = 1.0 * texture(original_image,reversed_texcoord);

}