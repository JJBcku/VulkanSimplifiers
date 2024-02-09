#include "../Other/pch.h"
#include "../Include/DevicePipelineData.h"

#include "DevicePipelineDataInternal.h"

namespace VulkanSimplified
{
	DevicePipelineData::DevicePipelineData(DevicePipelineDataInternal& ref) : _internal(ref)
	{
	}

	DevicePipelineData::~DevicePipelineData()
	{
	}

	ListObjectID<AutoCleanupDescriptorSetLayout> DevicePipelineData::AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList)
	{
		return _internal.AddDescriptorSetLayout(bindingsIDList);
	}
	ListObjectID<AutoCleanupPipelineLayout> DevicePipelineData::AddPipelineLayout(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts,
		const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges)
	{
		return _internal.AddPipelineLayout(descriptorSetLayouts, pushConstantRanges);
	}
	ListObjectID<AutoCleanupRenderPass> DevicePipelineData::AddRenderPass(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptors, const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptions, const std::vector<ListObjectID<VkSubpassDependency>>& subpassDependencies)
	{
		return _internal.AddRenderPass(attachmentDescriptors, subpassDescriptions, subpassDependencies);
	}
}