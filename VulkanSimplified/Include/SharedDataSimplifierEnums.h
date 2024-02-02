#pragma once

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
}