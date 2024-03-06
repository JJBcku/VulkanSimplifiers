#include "../Other/pch.h"
#include "../Include/Device/DeviceCoreSimplifier.h"

#include "DeviceCoreSimplifierInternal.h"

#include "ShaderModulesSimplifierInternal.h"
#include "../Include/Device/ShaderModulesSimplifier.h"

namespace VulkanSimplified
{

	DeviceCoreSimplifier::DeviceCoreSimplifier(DeviceCoreSimplifierInternal& reference) : _internal(reference)
	{
	}

	DeviceCoreSimplifier::~DeviceCoreSimplifier()
	{
	}

	void DeviceCoreSimplifier::WaitForIdleness()
	{
		_internal.WaitForIdleness();
	}

}