#include "pch.h"
#include "Include/ShaderModulesSimplifier.h"

#include "ShaderModulesSimplifierInternal.h"

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