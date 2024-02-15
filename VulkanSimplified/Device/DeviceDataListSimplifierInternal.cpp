#include "../Other/pch.h"
#include "DeviceDataListSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceDataListSimplifierInternal::DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo,
		const DeviceSettings& deviceSettings, const SharedDataSimplifierCoreInternal& sharedDataList, const SwapchainSimplifierInternal& swapchain) : _sharedDataList(sharedDataList),
		_deviceCore(device, deviceInfo, deviceSettings), _shaderModules(_deviceCore.GetDevice()), _pipelineData(_deviceCore.GetDevice(), _sharedDataList, _shaderModules),
		_imageData(_deviceCore.GetDevice(), swapchain, _pipelineData), _commandBuffers(_deviceCore, _imageData, _pipelineData, _sharedDataList),
		_synchronizationData(_deviceCore.GetDevice())
	{
		_ppadding = nullptr;
	}

	DeviceDataListSimplifierInternal::~DeviceDataListSimplifierInternal()
	{
	}

	DeviceCoreSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceCoreSimplifier()
	{
		return _deviceCore;
	}

	ShaderModulesSimplifierInternal& DeviceDataListSimplifierInternal::GetShaderModulesSimplifier()
	{
		return _shaderModules;
	}

	DevicePipelineDataInternal& DeviceDataListSimplifierInternal::GetDevicePipelineData()
	{
		return _pipelineData;
	}

	DeviceImageSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceImageSimplifier()
	{
		return _imageData;
	}

	DeviceCommandBufferSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceCommandBufferSimplifier()
	{
		return _commandBuffers;
	}

	DeviceSynchronizationSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceSynchronizationSimplifier()
	{
		return _synchronizationData;
	}

	const DeviceCoreSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceCoreSimplifier() const
	{
		return _deviceCore;
	}

	const ShaderModulesSimplifierInternal& DeviceDataListSimplifierInternal::GetShaderModulesSimplifier() const
	{
		return _shaderModules;
	}

	const DevicePipelineDataInternal& DeviceDataListSimplifierInternal::GetDevicePipelineData() const
	{
		return _pipelineData;
	}

	const DeviceImageSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceImageSimplifier() const
	{
		return _imageData;
	}

	const DeviceCommandBufferSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceCommandBufferSimplifier() const
	{
		return _commandBuffers;
	}

	const DeviceSynchronizationSimplifierInternal& DeviceDataListSimplifierInternal::GetDeviceSynchronizationSimplifier() const
	{
		return _synchronizationData;
	}

}