#version 430
uniform sampler2D result;
in vec3 pos;
in vec2 tex_coord;

out vec4 fragcolor;

void main(void){
	fragcolor = texture2D(result, tex_coord);
}