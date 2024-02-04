#pragma once

#include "DeviceCoreSimplifierInternal.h"
#include "ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;

	class DeviceDataListSimplifierInternal
	{
		const SharedDataSimplifierCoreInternal& _sharedDataList;
		void* _ppadding;

		DeviceCoreSimplifierInternal _deviceCore;
		ShaderModulesSimplifierInternal _shaderModules;

	public:
		DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings, const SharedDataSimplifierCoreInternal& sharedDataList);
		~DeviceDataListSimplifierInternal();

		DeviceDataListSimplifierInternal(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal(DeviceDataListSimplifierInternal&&) noexcept = delete;

		DeviceDataListSimplifierInternal& operator=(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal& operator=(DeviceDataListSimplifierInternal&& other) noexcept = delete;

		DeviceCoreSimplifierInternal& GetDeviceCoreSimplifier();
		ShaderModulesSimplifierInternal& GetShaderModulesSimplifier();

		const DeviceCoreSimplifierInternal& GetConstDeviceCoreSimplifierInternal() const;
		const ShaderModulesSimplifierInternal& GetConstShaderModulesSimplifier() const;
	};
}

