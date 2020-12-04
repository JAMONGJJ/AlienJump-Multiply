#version 410

uniform sampler2D Texture;
in vec2 fragUV;

out vec4 outCol;

void main(){
    outCol = texture(Texture, fragUV);
    outCol.a = min(outCol.a, 0.1);
}