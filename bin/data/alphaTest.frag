#version 410

uniform sampler2D Texture;
in vec2 fragUV;

out vec4 outCol;

void main(){
    outCol = texture(Texture, fragUV);
    if (outCol.a < 1.0)
        discard;
}