#pragma once

#include "VulkanSimplifierListTemplate.h"
#include "SharedDataSimplifierEnums.h"

struct VkAttachmentDescription;
struct VkAttachmentReference;

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SharedDataRenderPassElementsInternal;

	struct SubpassDescriptionData;

	class SharedDataRenderPassElements
	{
		SharedDataRenderPassElementsInternal& _internal;

	public:
		SharedDataRenderPassElements(SharedDataRenderPassElementsInternal& ref);
		~SharedDataRenderPassElements();

		SharedDataRenderPassElements& operator=(const SharedDataRenderPassElements&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode, AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);
		ListObjectID<VkAttachmentReference> AddAttachmentReference(uint32_t attachment, AttachmentLayout layout);

		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);
	};
}
