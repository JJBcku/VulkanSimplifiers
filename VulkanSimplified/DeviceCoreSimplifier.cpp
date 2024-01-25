#include "pch.h"
#include "Include/DeviceCoreSimplifier.h"

#include "DeviceCoreSimplifierInternal.h"

#include "ShaderModulesSimplifierInternal.h"
#include "Include/ShaderModulesSimplifier.h"

namespace VulkanSimplified
{

	DeviceCoreSimplifier::DeviceCoreSimplifier(DeviceCoreSimplifierInternal& reference) : _internal(reference)
	{
	}

	DeviceCoreSimplifier::~DeviceCoreSimplifier()
	{
	}

	ShaderModulesSimplifier DeviceCoreSimplifier::GetShaderModulesSimplifier()
	{
		return _internal.GetShaderModulesSimplifier();
	}

}