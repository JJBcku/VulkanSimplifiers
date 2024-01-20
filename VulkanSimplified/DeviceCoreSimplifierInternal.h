#pragma once

#include "Include/BasicsSimplifierSharedStructs.h"
#include "Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	struct SimplifiedDeviceInfo;
	struct DeviceSettings;

	class DeviceCoreSimplifierInternal
	{
		VkDevice _device;
		SimplifiedDeviceInfo _info;
		DeviceSettings _settings;

		VkQueue _graphicQueue, _computeQueue, _transferQueue, _paddingQueue;

		VkDeviceQueueCreateInfo CreateQueueInfo(uint32_t queueFamily, const float& priority) const;

	public:
		DeviceCoreSimplifierInternal(VkPhysicalDevice device, SimplifiedDeviceInfo deviceInfo, DeviceSettings deviceSettings);
		~DeviceCoreSimplifierInternal();
	};
}


