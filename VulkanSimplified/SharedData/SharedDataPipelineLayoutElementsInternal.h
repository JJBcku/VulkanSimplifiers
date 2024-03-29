#pragma once

#include "../Other/VulkanSimplifierListTemplate.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second);
bool operator==(const VkDescriptorSetLayoutBinding& first, const VkDescriptorSetLayoutBinding& second);

namespace VulkanSimplified
{
	class SharedDataPipelineLayoutElementsInternal
	{
		ListTemplate<VkPushConstantRange> _pushConstantRanges;
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

		VkDescriptorSetLayoutBinding GetDescriptorSetLayoutBinding(ListObjectID<VkDescriptorSetLayoutBinding> bindingID) const;
		std::vector<VkDescriptorSetLayoutBinding> GetDescriptorSetLayoutBindingsList(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingIDs) const;

		VkPushConstantRange GetPushConstantsRange(ListObjectID<VkPushConstantRange> pushConstantsID) const;
		std::vector<VkPushConstantRange> GetPushConstantsRangesList(const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantsIDs) const;
	};
}
