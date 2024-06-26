#version 460

#extension GL_EXT_scalar_block_layout : enable

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 inPos;

layout (location = 0) out vec4 outColor;

layout (std430, set = 0, binding = 0) uniform UniformBufferObject
{
	mat4 model;
	mat4 view;
	mat4 projection;
} ubo;

void main()
{
	gl_Position = ubo.projection * ubo.view * ubo.model * vec4(inPos, 0.0, 1.0);
	outColor = inColor;
}