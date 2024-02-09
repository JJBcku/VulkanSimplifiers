#pragma once

#include "../Include//VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkAttachmentDescription& first, const VkAttachmentDescription& second);
bool operator==(const VkAttachmentReference& first, const VkAttachmentReference& second);

namespace VulkanSimplified
{
	class MainSimplifierInternal;
	class BasicsSimplifierInternal;

	class SharedDataRenderPassElementsInternal
	{
		const MainSimplifierInternal& _main;
		void* _ppadding;

		ListTemplate<VkAttachmentDescription> _attachmentDescriptions;
		ListTemplate<VkAttachmentReference> _attachmentReference;

		VkImageLayout GetImageLayout(AttachmentLayout layout);

	public:
		SharedDataRenderPassElementsInternal(size_t reserve, const MainSimplifierInternal& ref);
		~SharedDataRenderPassElementsInternal();

		SharedDataRenderPassElementsInternal(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		SharedDataRenderPassElementsInternal& operator=(const SharedDataRenderPassElementsInternal&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode,  AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);

		ListObjectID<VkAttachmentReference> AddAttachmentReference(uint32_t attachment, AttachmentLayout layout);
	};
}
