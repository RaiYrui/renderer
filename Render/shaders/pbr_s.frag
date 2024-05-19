#version 430 core
const float PI = 3.14159265359;
in vec2 UV;
in vec3 Fragpos;
in vec3 Normal;
in vec3 orinormal;
in vec4 cpos;
out vec4 FragColor;

uniform vec3 Lightpos[100];
uniform vec4 Lightcolor[100];
uniform float Intensity[100];
uniform vec3 Campos;
uniform int Lightnum;
uniform vec3 Lightdir;
uniform float time;
uniform vec4 NST;
uniform vec4 color;
uniform float metallic;
uniform float roughness;
uniform float ao;
uniform sampler2D maintex;
uniform samplerCube cubemap;
uniform sampler2D height;
uniform sampler2D ddzx;

vec3 getNormalFromMap()
{
    vec3 tangentNormal = (texture(maintex, vec2(UV.x-(time*0.1f),UV.y+(time*0.1f)) * NST.xy  * NST.zw).rgb * 2.0 - 1.0)*5;

    vec3 Q1  = dFdx(Fragpos);
    vec3 Q2  = dFdy(Fragpos);
    vec2 st1 = dFdx(UV);
    vec2 st2 = dFdy(UV);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
float saturate(float value) {
    return clamp(value, 0.0, 1.0);
}
vec3 blendNormals(vec3 n1, vec3 n2,float factor) {
    return normalize(mix(n1,n2,factor));
}
void main(){
    vec3 nmap = getNormalFromMap();
	vec3 N = normalize(Normal);
    vec3 V = normalize(Campos - Fragpos);
    vec4 diffuse = color;
   vec3 blendn = blendNormals(nmap,orinormal,0.6f);
   // vec3 blendn = orinormal;
     //’€…‰
    float ratio = 1.00 / 1.52;
    vec3 refraction = refract(-V, blendn, ratio);
	vec4 refracolor = vec4(texture(cubemap,refraction).rgb,1.0f);
    diffuse.rgb = mix(refracolor.rgb,diffuse.rgb,diffuse.a);
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, diffuse.rgb, metallic);
    vec3 Lo = vec3(0.0);
     //∑¥…‰
    float f = pow(1.0 - clamp(dot(blendn,V),0.0,1.0),3.0f);
	vec3 R = reflect(-V,blendn);
	vec4 refcolor = vec4(texture(cubemap,R).rgb,1.0f);
    //—’…´∆´“∆
    for(int i = 0; i < Lightnum; ++i) 
    {
        vec3 L = normalize(-Lightdir);
        vec3 H = normalize(V + L);
        float distance    = length(Lightpos[i] - Fragpos);
        float attenuation = 1.0 / (distance * distance);
        float NdotL = max(dot(blendn, L), 0.0);
        vec3 lightcolor = Lightcolor[i].rgb;
       lightcolor.b *= NdotL;
       lightcolor.g *= clamp(NdotL,0.3,1.0);
        vec3 radiance     = lightcolor.rgb * attenuation * Intensity[i];        

        float NDF = DistributionGGX(blendn, H, roughness);        
        float G   = GeometrySmith(blendn, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;     

        vec3 nominator    = NDF * G * F;
        float denominator = 4.0 * max(dot(blendn, V), 0.0) * max(dot(blendn, L), 0.0) + 0.001; 
        vec3 specular     = nominator / denominator;          
        Lo += (kD * diffuse.rgb / PI + specular) * radiance * NdotL* Intensity[i]; 
        refcolor *= NdotL;
        //diffuse.rgb *= NdotL;
    }   
    diffuse.rgb = mix(diffuse.rgb,(refcolor.rgb),f);
    vec3 ambient = vec3(0.05) * diffuse.rgb * ao;
    vec3 res = ambient + Lo;
    float w = (Lo.r+Lo.g+Lo.b)/3;
    float foam = texture(ddzx,UV).r;
    res = res / (res + vec3(1.0));
    res = pow(res, vec3(1.0/2.2));
    //ŒÌ–ß
    //float distance = cpos.z/cpos.w;
    //res = mix(res,vec3(0.2,0.1,0.05),(distance-0.99)*100);
    //vec4 colorrr = texture(height,UV);
    FragColor = vec4(res+max((0.01-foam)*0.5,0), clamp(w,diffuse.a,1.0));
    //FragColor = colorrr;

}