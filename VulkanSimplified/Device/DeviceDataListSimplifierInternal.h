#pragma once

#include "DeviceCoreSimplifierInternal.h"
#include "ShaderModulesSimplifierInternal.h"
#include "DevicePipelineDataInternal.h"
#include "DeviceImageSimplifierInternal.h"
#include "DeviceCommandBufferSimplifierInternal.h"
#include "DeviceSynchronizationSimplifierInternal.h"
#include "DeviceMemorySimplifierInternal.h"

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
		DeviceCommandBufferSimplifierInternal _commandBuffers;
		DeviceSynchronizationSimplifierInternal _synchronizationData;
		DeviceMemorySimplifierInternal _memoryData;

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
		DeviceCommandBufferSimplifierInternal& GetDeviceCommandBufferSimplifier();
		DeviceSynchronizationSimplifierInternal& GetDeviceSynchronizationSimplifier();
		DeviceMemorySimplifierInternal& GetDeviceMemorySimplifier();

		const DeviceCoreSimplifierInternal& GetDeviceCoreSimplifier() const;
		const ShaderModulesSimplifierInternal& GetShaderModulesSimplifier() const;
		const DevicePipelineDataInternal& GetDevicePipelineData() const;
		const DeviceImageSimplifierInternal& GetDeviceImageSimplifier() const;
		const DeviceCommandBufferSimplifierInternal& GetDeviceCommandBufferSimplifier() const;
		const DeviceSynchronizationSimplifierInternal& GetDeviceSynchronizationSimplifier() const;
		const DeviceMemorySimplifierInternal& GetDeviceMemorySimplifier() const;
	};
}

