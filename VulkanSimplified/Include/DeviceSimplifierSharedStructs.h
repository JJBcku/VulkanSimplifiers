#pragma once

#include "DeviceSimplifierSharedEnums.h"
#include "VulkanSimplifierListTemplate.h"

struct VkDescriptorSetLayoutBinding;

namespace VulkanSimplified
{
	struct DeviceSettings
	{
		bool unrestrictedDepth;
		bool fillRectangleNV;
		bool swapchainExtension;
		char padding[5];

		DeviceSettings();
	};

	struct SwapchainSettings
	{
		SwapchainFormatType format;
		SwapchainPresentMode presentMode;
		SwapchainImageAmount imageAmount;
	};
}