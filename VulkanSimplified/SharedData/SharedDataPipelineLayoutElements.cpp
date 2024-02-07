#include "../Other/pch.h"
#include "../Include/SharedDataPipelineLayoutElements.h"

#include "SharedDataPipelineLayoutElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineLayoutElements::SharedDataPipelineLayoutElements(SharedDataPipelineLayoutElementsInternal& ref) : _internal(ref)
	{
	}

	SharedDataPipelineLayoutElements::~SharedDataPipelineLayoutElements()
	{
	}

	ListObjectID<VkPushConstantRange> SharedDataPipelineLayoutElements::AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size)
	{
		return _internal.AddPushConstantRange(shaderStages, offset, size);
	}

	ListObjectID<VkDescriptorSetLayoutBinding> SharedDataPipelineLayoutElements::AddDescriptorSetLayoutBinding(uint32_t binding, PipelineLayoutDescriptorType descriptorType, uint32_t descriptorCount, ShaderStageFlags shaderStages)
	{
		return _internal.AddDescriptorSetLayoutBinding(binding, descriptorType, descriptorCount, shaderStages);
	}

}