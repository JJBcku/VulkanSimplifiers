#include "../pch.h"
#include "../Include/DeviceDataListSimplifier.h"

#include "DeviceDataListSimplifierInternal.h"

#include "../Include/DeviceCoreSimplifier.h"
#include "../Include/ShaderModulesSimplifier.h"

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

}
