#version 430 core
in vec3 Fragpos;
out vec4 FragColor;
uniform samplerCube cubemap;
uniform vec3 lightdir;

void main(){
	vec3 envColor = texture(cubemap,Fragpos).rgb;
    envColor = envColor/(envColor+vec3(1.0));
    envColor = pow(envColor,vec3(1.0/2.2));
    float hdotl = clamp(dot(vec3(0,1,0),-lightdir),0.02,1.0);
    //vec3 rc = vec3(1,0.2,0.1);
    //vec3 c = envColor*hdotl;
    //vec3 fcolor = mix(c,rc*c,1-hdotl);
    FragColor = vec4(envColor*hdotl,1.0);
}
