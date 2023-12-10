#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP; // Model View Projection Martix

void main()
{
    gl_Position = position * u_MVP;
    v_TexCoord = TexCoord;
}

#shader fragment
#version 330 core
layout (location=0) out vec4 FragColor;  

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, v_TexCoord);
    //FragColor = vec4(v_TexCoord, 0.0, 1.0);
}
