#include "../Other/pch.h"
#include "../Include/Device/ShaderModulesSimplifier.h"

#include "ShaderModulesSimplifierInternal.h"

#include "../Include/Common/ListObjectID.h"

namespace VulkanSimplified
{

	ShaderModulesSimplifier::ShaderModulesSimplifier(ShaderModulesSimplifierInternal& reference) : _internal(reference)
	{
	}

	ShaderModulesSimplifier::~ShaderModulesSimplifier()
	{
	}

	ListObjectID<ShaderContainer> ShaderModulesSimplifier::CreateShaderModule(const std::vector<unsigned char>& shaderCode)
	{
		return _internal.CreateShaderModule(shaderCode);
	}

}