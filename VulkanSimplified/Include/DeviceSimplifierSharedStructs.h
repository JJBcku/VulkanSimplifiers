#pragma once

namespace VulkanSimplified
{
	struct DeviceSettings
	{
		bool depthUnrestricted;
		char padding[7];

		DeviceSettings();
	};
}