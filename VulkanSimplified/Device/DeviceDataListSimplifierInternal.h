#pragma once

#include "DeviceCoreSimplifierInternal.h"
#include "ShaderModulesSimplifierInternal.h"
#include "DevicePipelineDataInternal.h"
#include "DeviceImageSimplifierInternal.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;
	class SwapchainSimplifierInternal;

	class DeviceDataListSimplifierInternal
	{
		const SharedDataSimplifierCoreInternal& _sharedDataList;
		void* _ppadding;

		DeviceCoreSimplifierInternal _deviceCore;
		ShaderModulesSimplifierInternal _shaderModules;
		DevicePipelineDataInternal _pipelineData;
		DeviceImageSimplifierInternal _imageData;

	public:
		DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings,
			const SharedDataSimplifierCoreInternal& sharedDataList, const SwapchainSimplifierInternal& swapchain);
		~DeviceDataListSimplifierInternal();

		DeviceDataListSimplifierInternal(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal(DeviceDataListSimplifierInternal&&) noexcept = delete;

		DeviceDataListSimplifierInternal& operator=(const DeviceDataListSimplifierInternal&) noexcept = delete;
		DeviceDataListSimplifierInternal& operator=(DeviceDataListSimplifierInternal&& other) noexcept = delete;

		DeviceCoreSimplifierInternal& GetDeviceCoreSimplifier();
		ShaderModulesSimplifierInternal& GetShaderModulesSimplifier();
		DevicePipelineDataInternal& GetDevicePipelineData();
		DeviceImageSimplifierInternal& GetDeviceImageSimplifier();

		const DeviceCoreSimplifierInternal& GetDeviceCoreSimplifier() const;
		const ShaderModulesSimplifierInternal& GetShaderModulesSimplifier() const;
		const DevicePipelineDataInternal& GetDevicePipelineData() const;
		const DeviceImageSimplifierInternal& GetDeviceImageSimplifier() const;
	};
}

