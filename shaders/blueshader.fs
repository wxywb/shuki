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
layout (location = 1)out vec4 BrightColor;


void main()
{
 
    vec3 nn = vec3(texture(normal_texture,TexCoord));
    nn = nn * 4.0 - 3.0;
   //vec3 nn = vec3(0,0,1);
    vec3 ff = transMat * nn;
    vec3  light_direction = normalize(lightpos - positions);
    float density = max(dot(light_direction,ff),0);
   //FragColor = vec4(0.0, 0.0, 0.3 + 1.0 * density, 1.0);
  //  FragColor = texture(skybox, TexCoords);
  // FragColor = texture(normal_texture,TexCoord)/2 + texture(diffuse_texture,TexCoord)/2;
 //  FragColor = texture(diffuse_texture,TexCoord);

 //  
   // vec3 ff = clamp(transMat * nn,0.0,1.0);
    // if(ff.z > 0.5 && ff.z > ff.x)
    // {
    //     BrightColor = vec4(ff,1.0); 
    // }else{
    //     BrightColor = vec4(0.0,0.0,0.0,1.0);
    // }
     BrightColor = vec4(0.0,0.0,1.0,1.0);
    FragColor = vec4(ff,1.0);
   //  FragColor = vec4(normalize(normal),1.0) ;
    // FragColor = vec4(ff ,1.0);
     //vec4 texcolor = texture(diffuse_texture ,TexCoord);
    // FragColor = 0.1 * texcolor + texcolor * density*2;
    //  FragColor = texture(normal_texture,TexCoord);// vec4(tex_normal,1.0);//texture(diffuse_texture,TexCoord);
}
