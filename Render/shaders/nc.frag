#version 430 core
in vec3 Fragpos;
in vec2 UV;
in vec3 Normal;
out vec4 FragColor;
uniform vec3 Lightdir;
uniform vec4 color;
uniform vec3 Campos;
uniform sampler2D h;
void main(){
	vec3 ambient = color.rgb * 0.3f;
	vec3 N = normalize(Normal);
	float ndl = clamp(dot(N,-Lightdir),0,1);
	vec3 diff = ndl * color.rgb;
	vec3 V = normalize(Campos - Fragpos);
	vec3 H = normalize(V + (-Lightdir));
	float spec = pow(clamp(dot(N,H),1,0),32);
	vec3 specolor = vec3(1,1,1) * spec * 0.5f;
	//vec4 clorrr = texture(h,UV);
	FragColor = vec4(ambient + diff + specolor,1.0f);
	//FragColor = clorrr;
}