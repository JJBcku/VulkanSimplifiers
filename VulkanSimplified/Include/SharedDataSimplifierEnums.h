#pragma once

typedef uint32_t VkPipelineStageFlags;

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t
	{
		VEC2_FLOAT = 1,
		VEC2_DOUBLE = 2,
		VEC4_FLOAT = 4,
		VEC4_DOUBLE = 8,
	};

	enum class ShaderStageType : uint64_t
	{
		VERTEX = 1,
		FRAGMENT = 2,
	};

	enum ShaderStageFlags : uint64_t
	{
		NONE = 0,
		VERTEX = 1,
		FRAGMENT = 2,
	};

	enum class TopologySetting : uint64_t
	{
		POINT = 1,
		LINE = 2,
		LINE_STRIP = 4,
		LINE_STRIP_RESTARTABLE = 8,
		TRIANGLE = 0X10,
		TRIANGLE_STRIP = 0X20,
		TRIANGLE_STRIP_RESTARTABLE = 0X40,
		TRIANGLE_FAN = 0X80,
		TRIANGLE_FAN_RESTARTABLE = 0X100,
	};

	enum class PipelinePolygonMode : uint64_t
	{
		FILL = 1,
		LINE = 2,
		POINT = 4,
		RECTANGLE_NV = 8,
	};

	enum class PipelineCullMode : uint64_t
	{
		OFF = 1,
		FRONT = 2,
		BACK = 4,
	};

	enum class PipelineMultisampleCount : uint64_t
	{
		SAMPLE_1 = 1,
		SAMPLE_2 = 2,
		SAMPLE_4 = 4,
		SAMPLE_8 = 8,
		SAMPLE_16 = 16,
		SAMPLE_32 = 32,
		SAMPLE_64 = 64,
	};

	enum class PipelineDepthCompare : uint64_t
	{
		LESS = 1,
		EQUAL = 2,
		LESS_OR_EQUAL = 4,
		GREATER = 8,
		GREATER_OR_EQUAL = 0x10,
	};

	enum class PipelineBlendSettings : uint64_t
	{
		OFF = 1,
		STANDARD_NO_ALPHA = 2,
		STANDARD_ALPHA_ONE = 4,
	};

	enum class PipelineLayoutDescriptorType : uint64_t
	{
		SAMPLER = 1,
		COMBINED_SAMPLER = 2,
		SAMPLED_IMAGE = 4,
		STORAGE_IMAGE = 8,
		UNIFORM_TEXEL_BUFFER = 0X10,
		STORAGE_TEXEL_BUFFER = 0X20,
		UNIFORM_BUFFER = 0X40,
		STORAGE_BUFFER = 0X80,
		UNIFORM_BUFFER_DYNAMIC = 0X100,
		STORAGE_BUFFER_DYNAMIC = 0X200,
	};

	enum class AttachmentStoreMode : uint64_t
	{
		STORE = 1,
		IGNORE = 2,
	};

	enum class AttachmentLoadMode : uint64_t
	{
		LOAD = 1,
		CLEAR = 2,
		IGNORE = 4,
	};

	enum class AttachmentLayout : uint64_t
	{
		IGNORED = 1,
		PRESENT = 2,
		COLOR = 4,
	};
	
	enum class PipelineBindPoint : uint64_t
	{
		GRAPHIC = 1,
		COMPUTE = 2,
	};

	enum PipelineStage : uint64_t
	{
		TOP = 1,
		BOTTOM = 2,
		COLOR_ATTACHMENT_OUTPUT = 4,
	};

	VkPipelineStageFlags TranslatePipelineStage(PipelineStage stages);

	enum PipelineAccess : uint64_t
	{
		COLOR_READ = 1,
		COLOR_WRITE = 2,
		NO_ACCESS = 0,
	};
}