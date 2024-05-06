#include "../Other/pch.h"
#include "../Include/Device/DeviceDataListSimplifier.h"

#include "DeviceDataListSimplifierInternal.h"

#include "../Include/Device/DeviceCoreSimplifier.h"
#include "../Include/Device/ShaderModulesSimplifier.h"
#include "../Include/Device/DevicePipelineData.h"
#include "../Include/Device/DeviceImageSimplifier.h"
#include "../Include/Device/DeviceCommandBufferSimplifier.h"
#include "../Include/Device/DeviceSynchronizationSimplifier.h"
#include "../Include/Device/DeviceMemorySimplifier.h"
#include "../Include/Device/DeviceDataBufferSimplifier.h"
#include "../Include/Device/DeviceDescriptorSimplifier.h"

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

	DeviceSynchronizationSimplifier DeviceDataListSimplifier::GetDeviceSynchronizationSimplifier()
	{
		return DeviceSynchronizationSimplifier(_internal.GetDeviceSynchronizationSimplifier());
	}

	DeviceMemorySimplifier DeviceDataListSimplifier::GetDeviceMemorySimplifier()
	{
		return DeviceMemorySimplifier(_internal.GetDeviceMemorySimplifier());
	}

	DeviceDataBufferSimplifier DeviceDataListSimplifier::GetDeviceDataBufferSimplifier()
	{
		return DeviceDataBufferSimplifier(_internal.GetDeviceDataBufferSimplifier());
	}

	DeviceDescriptorSimplifier DeviceDataListSimplifier::GetDeviceDescriptorSimplifier()
	{
		return DeviceDescriptorSimplifier(_internal.GetDeviceDescriptorSimplifier());
	}

}
