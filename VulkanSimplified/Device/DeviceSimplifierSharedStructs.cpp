#include "../Other/pch.h"
#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	DeviceSettings::DeviceSettings()
	{
		unrestrictedDepth = false;
		fillRectangleNV = false;
		swapchainExtension = false;
		memset(padding, 0, sizeof(padding));
	}
}

