#version 330 core
out vec4 FragColor;
uniform float ourColor;
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    FragColor = vec4(ourColor, 0, 0, 1);
    FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0 - texCoord.x, texCoord.y)), 0.2);
}
