#version 330 core

out vec4 FragColor;
in vec2 ourTexCoord;

uniform sampler2D ourTexture;

const vec4 ourColor = vec4(0.0, 0.0, 0.0, 0.0);

void main() {
    vec4 texColor = texture(ourTexture, ourTexCoord);
    if (texColor.a > 0.0) {
        FragColor = mix(texColor, ourColor, ourColor.a);
    } else {
        FragColor = texColor;
    }
}
