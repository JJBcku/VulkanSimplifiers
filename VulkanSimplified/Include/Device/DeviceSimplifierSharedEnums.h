#pragma once

namespace VulkanSimplified
{
	enum class BasePipelineIDType : uint64_t
	{
		NONE = 0,
		ALREADY_CREATED = 1,
		IN_CURRENT_LIST = 2,
	};

	enum class QueueFamilyType : uint64_t
	{
		TRANSFER = 1,
		COMPUTE = 2,
		GRAPHICS = 4,
	};

	enum class PrimaryBufferRecordingSettings : uint64_t
	{
		STANDARD = 1,
		SINGLE_USE = 2,
		MULTI_SUBMIT = 4,
	};

	enum class MemoryPropertiesIDType : uint64_t
	{
		NONE = 0,
		UNCACHED = 1,
		CACHED_INCOHERENT = 2,
		CACHED_COHERENT = 3,
	};

	enum class MemoryType : uint64_t
	{
		EXCLUSIVE = 1,
		EXTERNAL = 2,
		SHARED = 3,
	};
}