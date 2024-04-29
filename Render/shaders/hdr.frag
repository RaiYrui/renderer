#version 430 core
in vec2 UV;
out vec4 FragColor;
uniform sampler2D src;
uniform float exposure;
void main(){
	const float gamma = 2.2;
    vec3 hdrColor = texture(src, UV).rgb;

    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0f);
}