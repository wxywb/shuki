#version 430
in vec3 positions; 
in float color;
in vec2 TexCoord;
in vec3 normal;
in vec3 tangent;
in vec3 TexCoords;
//out vec4 FragColor;
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform samplerCube skybox;
vec3 lightpos = vec3(100.0,0.0,0.0);
in mat3 transMat;

layout (location = 0)out vec4 FragColor;
layout (location = 1)out vec4 gPosition;
layout (location = 2)out vec4 gDepth;



void main()
{
 
    vec3 nn = vec3(texture(normal_texture,TexCoord));
    nn = nn * 4.0 - 3.0;
    vec3 ff = transMat * nn;
    vec3  light_direction = normalize(lightpos - positions);
    float density = max(dot(light_direction,ff),0);

    FragColor = vec4(ff,1.0);
    gPosition = vec4(positions.z *- 1/10,0.0,0.0,0.0);
  //  gDepth = vec4(positions.z,0,0);
}
