#version 430 core
in vec2 UV;
out vec4 FragColor;

uniform sampler2D src;
uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 offset = 1.0 / textureSize(src, 0); 
    vec3 result = texture(src, UV).rgb * weight[0]; 
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(src, UV + vec2(offset.x * i, 0.0)).rgb * weight[i];
            result += texture(src, UV - vec2(offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(src, UV + vec2(0.0, offset.y * i)).rgb * weight[i];
            result += texture(src, UV - vec2(0.0, offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}