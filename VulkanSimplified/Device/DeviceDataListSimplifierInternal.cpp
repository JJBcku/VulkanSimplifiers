#include "../Other/pch.h"
#include "DeviceDataListSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceDataListSimplifierInternal::DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo,
		const DeviceSettings& deviceSettings, const SharedDataSimplifierCoreInternal& sharedDataList) : _sharedDataList(sharedDataList), _deviceCore(device, deviceInfo, deviceSettings),
		_shaderModules(_deviceCore.GetDevice())
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

	const DeviceCoreSimplifierInternal& DeviceDataListSimplifierInternal::GetConstDeviceCoreSimplifierInternal() const
	{
		return _deviceCore;
	}

	const ShaderModulesSimplifierInternal& DeviceDataListSimplifierInternal::GetConstShaderModulesSimplifier() const
	{
		return _shaderModules;
	}

}