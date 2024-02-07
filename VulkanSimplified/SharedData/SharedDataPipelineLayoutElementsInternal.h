#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"

#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second);
bool operator==(const VkDescriptorSetLayoutBinding& first, const VkDescriptorSetLayoutBinding& second);

namespace VulkanSimplified
{
	class SharedDataPipelineLayoutElementsInternal
	{
		ListTemplate<VkPushConstantRange> _pushConstants;
		ListTemplate<VkDescriptorSetLayoutBinding> _descriptorLayoutBindings;

	public:
		SharedDataPipelineLayoutElementsInternal(size_t reserve);
		~SharedDataPipelineLayoutElementsInternal();

		SharedDataPipelineLayoutElementsInternal(const SharedDataPipelineLayoutElementsInternal&) noexcept = delete;
		SharedDataPipelineLayoutElementsInternal(SharedDataPipelineLayoutElementsInternal&&) noexcept = delete;

		SharedDataPipelineLayoutElementsInternal& operator=(const SharedDataPipelineLayoutElementsInternal&) noexcept = delete;
		SharedDataPipelineLayoutElementsInternal& operator=(SharedDataPipelineLayoutElementsInternal&&) noexcept = delete;

		ListObjectID<VkPushConstantRange> AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size);
		ListObjectID<VkDescriptorSetLayoutBinding> AddDescriptorSetLayoutBinding(uint32_t binding, PipelineLayoutDescriptorType descriptorType, uint32_t descriptorCount, ShaderStageFlags shaderStages);
	};
}
