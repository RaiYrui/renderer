#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 bright;

in vec2 UV;
uniform sampler2D src;

void main(){
	FragColor = texture(src,UV);
	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.8)
        bright = vec4(FragColor.rgb, 1.0);
}