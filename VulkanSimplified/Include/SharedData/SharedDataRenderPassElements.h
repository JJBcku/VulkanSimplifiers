#pragma once

#include "SharedDataSimplifierEnums.h"

struct VkAttachmentDescription;
struct VkAttachmentReference;
struct VkSubpassDependency;

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SharedDataRenderPassElementsInternal;

	struct SubpassDescriptionData;

	template<class T>
	class ListObjectID;

	class SharedDataRenderPassElements
	{
		SharedDataRenderPassElementsInternal& _internal;

	public:
		SharedDataRenderPassElements(SharedDataRenderPassElementsInternal& ref);
		~SharedDataRenderPassElements();

		SharedDataRenderPassElements& operator=(const SharedDataRenderPassElements&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode, AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);
		ListObjectID<VkAttachmentReference> AddAttachmentReference(std::optional<uint32_t> attachment, AttachmentLayout layout);

		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments,
			ListObjectID<VkAttachmentReference> depthAttachment);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
			const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
			const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);

		ListObjectID<VkSubpassDependency> AddSubpassDependency(std::optional<uint32_t> srcSubpass, std::optional<uint32_t> dstSubpass,
			PipelineStage srcStageMask, PipelineStage dstStageMask, PipelineAccess srcAccessMask, PipelineAccess dstAccessMask);
	};
}
