#pragma once

namespace VulkanSimplified
{
	enum class SwapchainFormatType : uint64_t
	{
		EIGHT_BIT = 1,
		TEN_BIT = 2,
		TWELVE_BIT = 4,
		SIXTEEN_BIT = 8,
	};

	enum class SwapchainPresentMode : uint64_t
	{
		IMMEDIATE = 1,
		MAILBOX = 2,
		FIFO = 4,
	};

	enum class SwapchainImageAmount : uint64_t
	{
		MIN = 1,
		HALF_DIFFERENCE = 2,
		MAX = 4,
		MIN_PLUS_ONE = 8,
		MAX_MINUS_ONE = 0x10,
		HALF_AMOUNT = 0x20,
	};

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
}