#include "pch.h"
#include "Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	DeviceSettings::DeviceSettings()
	{
		depthUnrestricted = false;
		fillRectangleNV = false;
		swapchainExtension = false;
		memset(padding, 0, sizeof(padding));
	}
}

