#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkAttachmentDescription& first, const VkAttachmentDescription& second);
bool operator==(const VkAttachmentReference& first, const VkAttachmentReference& second);
bool operator==(const VkSubpassDependency& first, const VkSubpassDependency& second);

namespace VulkanSimplified
{
	class MainSimplifierInternal;
	class BasicsSimplifierInternal;

	struct SubpassDescriptionData
	{
		PipelineBindPoint _bindPoint = PipelineBindPoint::GRAPHIC;
		std::vector<ListObjectID<VkAttachmentReference>> _inputAttachments;
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
		ListTemplate<VkSubpassDependency> _subpassDependencies;

		VkImageLayout GetImageLayout(AttachmentLayout layout);

		VkPipelineStageFlags GetStageFlags(PipelineStage stageMask);
		VkAccessFlags GetAccessFlags(PipelineAccess accessMask);

	public:
		SharedDataRenderPassElementsInternal(size_t reserve, const MainSimplifierInternal& ref);
		~SharedDataRenderPassElementsInternal();

		SharedDataRenderPassElementsInternal(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		SharedDataRenderPassElementsInternal& operator=(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode,  AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);
		ListObjectID<VkAttachmentReference> AddAttachmentReference(uint32_t attachment, AttachmentLayout layout);

		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments,
			ListObjectID<VkAttachmentReference> depthAttachment);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
			const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>> &colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments);
		ListObjectID<SubpassDescriptionData> AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
			const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
			const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
			const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment);

		ListObjectID<VkSubpassDependency> AddSubpassDependency(std::optional<uint32_t> srcSubpass, std::optional<uint32_t> dstSubpass,
			PipelineStage srcStageMask, PipelineStage dstStageMask, PipelineAccess srcAccessMask, PipelineAccess dstAccessMask);

		VkAttachmentReference GetAttachmentReference(ListObjectID<VkAttachmentReference> attachmentReferenceID) const;
		std::vector<VkAttachmentReference> GetAttachmentReferencesList(const std::vector<ListObjectID<VkAttachmentReference>>& attachmentReferencesID) const;
		std::vector<VkAttachmentDescription> GetAttachmentDescriptionsList(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptorsIDs) const;
		std::vector<SubpassDescriptionData> GetSubpassDescriptionsDataList(const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptionsIDs) const;
		std::vector<VkSubpassDependency> GetSubpassDependenciesList(const std::vector<ListObjectID<VkSubpassDependency>>& subpassDescriptionsIDs) const;

	};
}

bool operator==(const VulkanSimplified::SubpassDescriptionData& first, const VulkanSimplified::SubpassDescriptionData& second) noexcept;