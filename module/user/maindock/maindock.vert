#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec2 textureCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

vec2 positions[6] = vec2[](
    vec2(-1.0,  1.0),
    vec2( 1.0,  1.0),
    vec2( 1.0, -1.0),
    vec2(-1.0,  1.0),
    vec2( 1.0, -1.0),
    vec2(-1.0, -1.0)
);

vec2 textureCoords[6] = vec2[](
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 1.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    textureCoord = textureCoords[gl_VertexIndex];
}