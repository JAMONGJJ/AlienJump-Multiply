#version 410

layout ( location = 0 ) in vec3 pos;
layout ( location = 3 ) in vec2 uv;

uniform float translation;
uniform mat4 model;

out vec2 fragUV;

void main(){
    vec3 tmp = pos - vec3(translation, 0.0, 0.0);
    if(tmp.x > -1.0 && tmp.x < 1.0)
        gl_Position = model * vec4(tmp, 1.0);
    fragUV = vec2(uv.x, 1.0 - uv.y);
}