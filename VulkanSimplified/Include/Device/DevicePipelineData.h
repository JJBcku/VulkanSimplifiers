#pragma once

#include "DeviceSimplifierSharedStructs.h"

struct VkAttachmentDescription;
struct VkSubpassDependency;
struct VkDescriptorSetLayoutBinding;
struct VkPushConstantRange;

namespace VulkanSimplified
{
	class DevicePipelineDataInternal;
	class AutoCleanupDescriptorSetLayout;
	class AutoCleanupPipelineLayout;
	class AutoCleanupRenderPass;

	struct SubpassDescriptionData;

	template<class T>
	class ListObjectID;

	class DevicePipelineData
	{
		DevicePipelineDataInternal& _internal;

	public:
		DevicePipelineData(DevicePipelineDataInternal& ref);
		~DevicePipelineData();

		DevicePipelineData& operator=(const DevicePipelineData&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList);
		ListObjectID<AutoCleanupPipelineLayout> AddPipelineLayout(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts,
			const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges);

		ListObjectID<AutoCleanupRenderPass> AddRenderPass(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptors,
			const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptions, const std::vector<ListObjectID<VkSubpassDependency>>& subpassDependencies);

		std::vector<ListObjectID<AutoCleanupGraphicsPipeline>> AddGraphicsPipelines(const std::vector<GraphicsPipelineCreateInfoList>& graphicsPipelinesDataLists);
	};
}
