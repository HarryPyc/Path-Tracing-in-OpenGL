#version 430            
layout(location = 0)in vec3 pos_attrib;
layout(location = 1)in vec2 tex_coord_attrib;

out vec3 pos;
out vec2 tex_coord;  

void main(void)
{
   gl_Position = vec4(pos_attrib, 1.0);
   pos = pos_attrib;
   tex_coord = tex_coord_attrib;
}