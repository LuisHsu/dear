#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(location = 0) out vec4 outColor;
layout(location = 0) in vec2 textureCoord;

void main() {
    outColor = texture(texSampler, textureCoord);
}
