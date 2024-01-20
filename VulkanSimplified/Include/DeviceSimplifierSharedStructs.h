#pragma once

#include "DeviceSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	struct DeviceSettings
	{
		bool depthUnrestricted;
		bool fillRectangleNV;
		char padding[6];

		DeviceSettings();
	};
}