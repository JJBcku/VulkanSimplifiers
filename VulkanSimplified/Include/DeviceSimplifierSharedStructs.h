#pragma once

#include "DeviceSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	struct DeviceSettings
	{
		bool depthUnrestricted;
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