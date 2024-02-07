#pragma once

#include "VulkanSimplifierListTemplate.h"

#include "SharedDataSimplifierEnums.h"

struct VkPushConstantRange;
struct VkDescriptorSetLayoutBinding;

namespace VulkanSimplified
{
	class SharedDataPipelineLayoutElementsInternal;

	class SharedDataPipelineLayoutElements
	{
		SharedDataPipelineLayoutElementsInternal& _internal;

	public:
		SharedDataPipelineLayoutElements(SharedDataPipelineLayoutElementsInternal& ref);
		~SharedDataPipelineLayoutElements();

		SharedDataPipelineLayoutElements(const SharedDataPipelineLayoutElements&) noexcept = delete;

		SharedDataPipelineLayoutElements& operator=(const SharedDataPipelineLayoutElements&) noexcept = delete;

		ListObjectID<VkPushConstantRange> AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size);
		ListObjectID<VkDescriptorSetLayoutBinding> AddDescriptorSetLayoutBinding(uint32_t binding, PipelineLayoutDescriptorType descriptorType, uint32_t descriptorCount, ShaderStageFlags shaderStages);
	};
}
