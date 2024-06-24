#pragma once

namespace VulkanSimplified
{
	enum class SwapchainFormatType : uint64_t;
	enum class SwapchainPresentMode : uint64_t;
	enum class SwapchainImageAmount : uint64_t;

	struct SwapchainSettings
	{
		SwapchainFormatType format;
		SwapchainPresentMode presentMode;
		SwapchainImageAmount imageAmount;

		SwapchainSettings();
	};
}