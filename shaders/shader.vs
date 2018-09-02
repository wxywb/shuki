#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 Texcoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;

uniform float mimori;
uniform mat4x4 WordMat;
uniform vec4 Vector;
uniform mat4x4 ProjMat;
uniform mat4x4 CameraMat;

out vec3 positions;
out float color;
out vec2 TexCoord;
out vec3 normal;
out vec3 tangent;

//vec3 lightpos = vec3(0.0,0.0,0.0);

void main()
{
    positions = Position;
    
 //   gl_Position =  ProjMat * CameraMat * vec4(Position.x, Position.y, Position.z, 1.0);
    gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
  
    color = 1.0f;   
    TexCoord = Texcoord;
    normal = Normal;
    tangent = Tangent;
}