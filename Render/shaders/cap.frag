#version 430 core
in vec3 Fragpos;
out vec4 FragColor;
uniform sampler2D map;
const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}
void  main(){
	vec2 uv = SampleSphericalMap(normalize(Fragpos));
    vec3 color = texture(map,uv).rgb;
    FragColor = vec4(color,1.0f);
}
