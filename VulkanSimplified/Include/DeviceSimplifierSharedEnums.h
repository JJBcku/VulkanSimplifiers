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
		HALF = 2,
		MAX = 4,
	};
}