#pragma once

#include "DeviceCoreSimplifierInternal.h"
#include "ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{
	class DeviceDataListSimplifierInternal
	{
		DeviceCoreSimplifierInternal _deviceCore;
		ShaderModulesSimplifierInternal _shaderModules;

	public:
		DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings);
		~DeviceDataListSimplifierInternal();

		DeviceDataListSimplifierInternal(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal(DeviceDataListSimplifierInternal&&) noexcept;

		DeviceDataListSimplifierInternal& operator=(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal& operator=(DeviceDataListSimplifierInternal&& other) noexcept;

		DeviceCoreSimplifierInternal& GetDeviceCoreSimplifier();
		ShaderModulesSimplifierInternal& GetShaderModulesSimplifier();

		const DeviceCoreSimplifierInternal& GetConstDeviceCoreSimplifierInternal() const;
		const ShaderModulesSimplifierInternal& GetConstShaderModulesSimplifier() const;
	};
}

