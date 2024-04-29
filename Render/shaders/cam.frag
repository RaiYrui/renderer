#version 430 core
in vec2 UV;
out vec4 FragColor;
uniform sampler2D src;
void main(){
   FragColor = texture(src, UV);
}