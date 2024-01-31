#include "pch.h"
#include "DeviceDataListSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceDataListSimplifierInternal::DeviceDataListSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings) : _deviceCore(device, deviceInfo, deviceSettings), _shaderModules(_deviceCore.GetDevice())
	{
	}

	DeviceDataListSimplifierInternal::~DeviceDataListSimplifierInternal()
	{
	}

	DeviceDataListSimplifierInternal::DeviceDataListSimplifierInternal(DeviceDataListSimplifierInternal&& other) noexcept : _deviceCore(std::move(other._deviceCore)), _shaderModules(std::move(other._shaderModules))
	{
	}

	DeviceDataListSimplifierInternal& DeviceDataListSimplifierInternal::operator=(DeviceDataListSimplifierInternal&& other) noexcept
	{
		this->_deviceCore = std::move(other._deviceCore);
		this->_shaderModules = std::move(other._shaderModules);

		return *this;
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