#shader vertex
#version 330 core
        
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
        
out vec4 v_Color;
out vec4 v_Pos;
//Model View Projection matrix
uniform mat4 u_MVP;


void main()
{
    gl_Position = u_MVP * position;
    v_Color = color;
    v_Pos = position;
};

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec4 v_Pos;

uniform vec4 u_Color;
uniform float u_ITime;

        
vec3 palette( float t)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    
    return a + b * cos(6.28318 * (c * t + d));
}

void main()
{
    vec4 texColor = v_Color;
    vec2 iResolution = vec2(800, 800);
    
    vec2 uv = (v_Pos.xy * 2.0 - iResolution.xy)  / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    vec3 newColor = vec3(0.0);
    
    
    for (float i = 0.0; i < 3.0; i++)
    {
        uv = fract(uv * 1.5) - 0.5;
    
        float d = length(uv) * exp(-length(uv0));
    
        vec3 col = palette(length(uv0) + i*.4 + u_ITime );
    
        d = sin(d * 4. + u_ITime) / 4.;
        d = abs(d);
    
        d = pow(0.01 / d, 1.2);
        
        //d = smoothstep(0.0, 0.1, d);
    
        finalColor += col * d;
        newColor = v_Color.xyz;
        newColor += col * d;
    }
        
    //color = vec4(finalColor, 1.0);
    
    color = vec4(newColor, 1.0);
};
