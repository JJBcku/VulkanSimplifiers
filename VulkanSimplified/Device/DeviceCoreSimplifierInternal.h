#pragma once

#include "../Include/BasicsSimplifierSharedStructs.h"
#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	struct SimplifiedDeviceInfo;
	struct DeviceSettings;

	class ShaderModulesSimplifierInternal;
	class ShaderModulesSimplifier;

	class DeviceCoreSimplifierInternal
	{
		VkDevice _device = VK_NULL_HANDLE;
		VkPhysicalDevice _physicalDevice;
		SimplifiedDeviceInfo _info;
		DeviceSettings _settings;

		VkQueue _graphicQueue, _computeQueue, _transferQueue, _paddingQueue;

		VkDeviceQueueCreateInfo CreateQueueInfo(uint32_t queueFamily, const float& priority) const;

		void CreateDevice(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings);
		void DestroyDevice();

	public:
		DeviceCoreSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings);
		DeviceCoreSimplifierInternal(const DeviceCoreSimplifierInternal&) noexcept = delete;
		DeviceCoreSimplifierInternal(DeviceCoreSimplifierInternal&& other) noexcept;
		~DeviceCoreSimplifierInternal();

		DeviceCoreSimplifierInternal& operator=(const DeviceCoreSimplifierInternal&) noexcept = delete;
		DeviceCoreSimplifierInternal& operator=(DeviceCoreSimplifierInternal&& other) noexcept;

		VkDevice GetDevice() const;
		VkPhysicalDevice GetPhysicalDevice() const;

		SimplifiedDeviceInfo GetDeviceInfo() const;

		uint32_t GetBestQueueForTheType(QueueFamilyType type) const;
	};
}


