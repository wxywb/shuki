#version 330
in vec3 positions; 
in float color;
in vec2 TexCoord;
in vec3 normal;
out vec4 FragColor;
uniform sampler2D ourTexture;

vec3 lightpos = vec3(100.0,0.0,0.0);

void main()
{
    //  FragColor = vec4(1.0 + positions.x * 0.5 - 0.5,color, 0.0, 1.0);
   
   
  // vec3  light_direction = normalize(lightpos - positions);
 //  float density = max(dot(light_direction,normal),0);
  // FragColor = vec4(0.0,1.0, 0.0, 1.0);
      vec2 z = vec2(TexCoord.x,1.0- TexCoord.y);
      FragColor = texture(ourTexture, z);
    
    
   // FragColor = vec4(normal.x,normal.y,normal.z, 1.0);


    //  FragColor = vec4(1.0,0.0, 0.0, 1.0);//texture(ourTexture, TexCoord);
}
