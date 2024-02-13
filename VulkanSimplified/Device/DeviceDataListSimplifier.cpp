#include "../Other/pch.h"
#include "../Include/DeviceDataListSimplifier.h"

#include "DeviceDataListSimplifierInternal.h"

#include "../Include/DeviceCoreSimplifier.h"
#include "../Include/ShaderModulesSimplifier.h"
#include "../Include/DevicePipelineData.h"
#include "../Include/DeviceImageSimplifier.h"
#include "../Include/DeviceCommandBufferSimplifier.h"

namespace VulkanSimplified
{

	DeviceDataListSimplifier::DeviceDataListSimplifier(DeviceDataListSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceDataListSimplifier::~DeviceDataListSimplifier()
	{
	}

	DeviceCoreSimplifier DeviceDataListSimplifier::GetDeviceCoreSimplifier()
	{
		return DeviceCoreSimplifier(_internal.GetDeviceCoreSimplifier());
	}

	ShaderModulesSimplifier DeviceDataListSimplifier::GetShaderModulesSimplifier()
	{
		return ShaderModulesSimplifier(_internal.GetShaderModulesSimplifier());
	}

	DevicePipelineData DeviceDataListSimplifier::GetDevicePipelineData()
	{
		return DevicePipelineData(_internal.GetDevicePipelineData());
	}

	DeviceImageSimplifier DeviceDataListSimplifier::GetDeviceImageSimplifier()
	{
		return DeviceImageSimplifier(_internal.GetDeviceImageSimplifier());
	}

	DeviceCommandBufferSimplifier DeviceDataListSimplifier::GetDeviceCommandBufferSimplifier()
	{
		return DeviceCommandBufferSimplifier(_internal.GetDeviceCommandBufferSimplifier());
	}

}
