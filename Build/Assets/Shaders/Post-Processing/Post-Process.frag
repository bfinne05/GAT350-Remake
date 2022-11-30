#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 
  
uniform sampler2D textureMap; 

const float screen_height = 600.0; 
  
uniform float offset; 
  
void main() 
{ 
 // wave 
 vec2 ttexcoord = texcoord; 
 ttexcoord.x += sin(ttexcoord.y * 30.0 + offset) / 100.0; 
 fcolor = texture(textureMap, ttexcoord); 
} 