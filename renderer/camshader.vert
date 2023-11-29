#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
//        gl_Position = vec4(pos*2-1, 1.0);
        gl_Position = projection * vec4(pos, 1.0);
//        gl_Position = vec4(pos, 1.0);

        TexCoord = tex;
}
