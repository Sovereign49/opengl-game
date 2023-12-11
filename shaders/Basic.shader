#shader vertex
#version 330 core
layout (location = 0) in vec4 position;

out vec2 v_TexCoord;

uniform mat4 u_MVP; // Model View Projection Martix

void main()
{
    gl_Position = u_MVP * position ;
    v_TexCoord = TexCoord;
}

#shader fragment
#version 330 core
layout (location=0) out vec4 FragColor;  

in vec2 v_TexCoord;

uniform vec4 u_Color;

void main()
{
    FragColor = u_Color;
}
