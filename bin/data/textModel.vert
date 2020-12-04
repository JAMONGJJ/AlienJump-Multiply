#version 410

layout ( location = 0 ) in vec3 pos;
layout ( location = 3 ) in vec2 uv;

uniform mat4 model;
out vec2 fragUV;

void main(){
    gl_Position = model * vec4(pos, 1.0);
    fragUV = vec2(uv.x, 1.0 - uv.y);
}