#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec2 texCoord;
out vec4 vertexColor; // specify a color output to the fragment shader
out vec3 ourColor;
out vec3 vertPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 transform;

void main()
{
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
    ourColor = aColor;
    vertPos = aPos;
    texCoord = aTextCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);

}