#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkAttachmentDescription& first, const VkAttachmentDescription& second);
bool operator==(const VkAttachmentReference& first, const VkAttachmentReference& second);

namespace VulkanSimplified
{
	class MainSimplifierInternal;
	class BasicsSimplifierInternal;

	struct SubpassDescriptionData
	{
		PipelineBindPoint _bindPoint = PipelineBindPoint::GRAPHIC;
		std::vector<ListObjectID<VkAttachmentReference>> _colorAttachments;
		std::vector<ListObjectID<VkAttachmentReference>> _resolveAttachments;
		std::vector<ListObjectID<VkAttachmentReference>> _preserveAttachments;
		std::optional<ListObjectID<VkAttachmentReference>> _depthAttachment;
	};

	class SharedDataRenderPassElementsInternal
	{
		const MainSimplifierInternal& _main;
		void* _ppadding;

		ListTemplate<VkAttachmentDescription> _attachmentDescriptions;
		ListTemplate<VkAttachmentReference> _attachmentReferences;
		ListTemplate<SubpassDescriptionData> _subpassDescriptions;

		VkImageLayout GetImageLayout(AttachmentLayout layout);

	public:
		SharedDataRenderPassElementsInternal(size_t reserve, const MainSimplifierInternal& ref);
		~SharedDataRenderPassElementsInternal();

		SharedDataRenderPassElementsInternal(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		SharedDataRenderPassElementsInternal& operator=(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode,  AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);
		ListObjectID<VkAttachmentReference> AddAttachmentReference(uint32_t attachment, AttachmentLayout layout);

		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>> &colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);
	};
}

bool operator==(const VulkanSimplified::SubpassDescriptionData& first, const VulkanSimplified::SubpassDescriptionData& second) noexcept;