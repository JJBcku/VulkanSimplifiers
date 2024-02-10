#include "../Other/pch.h"
#include "DeviceDataListSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceDataListSimplifierInternal::DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo,
		const DeviceSettings& deviceSettings, const SharedDataSimplifierCoreInternal& sharedDataList) : _sharedDataList(sharedDataList), _deviceCore(device, deviceInfo, deviceSettings),
		_shaderModules(_deviceCore.GetDevice()), _pipelineData(_deviceCore.GetDevice(), _sharedDataList, _shaderModules)
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

}