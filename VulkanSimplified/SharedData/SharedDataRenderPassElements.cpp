#include "../Other/pch.h"
#include "../Include/SharedDataRenderPassElements.h"

#include "SharedDataRenderPassElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataRenderPassElements::SharedDataRenderPassElements(SharedDataRenderPassElementsInternal& ref) : _internal(ref)
	{
	}

	SharedDataRenderPassElements::~SharedDataRenderPassElements()
	{
	}

	ListObjectID<VkAttachmentDescription> SharedDataRenderPassElements::AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias,
		ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount, AttachmentLoadMode loadMode, AttachmentStoreMode storeMode,
		AttachmentLayout initialLayout, AttachmentLayout finalLayout)
	{
		return _internal.AddAttachmentDescriptionWithSwapchainsFormat(mayAlias, instanceID, sampleCount, loadMode, storeMode, initialLayout, finalLayout);
	}

	ListObjectID<VkAttachmentReference> SharedDataRenderPassElements::AddAttachmentReference(uint32_t attachment, AttachmentLayout layout)
	{
		return _internal.AddAttachmentReference(attachment, layout);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		return _internal.AddSubpassDescriptorNoDepth(bindPoint, colorAttachments, preserveAttachments);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments,
		ListObjectID<VkAttachmentReference> depthAttachment)
	{
		return _internal.AddSubpassDescriptorWithDepth(bindPoint, colorAttachments, preserveAttachments, depthAttachment);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
		const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		return _internal.AddSubpassDescriptorWithResolveAttachmentsNoDepth(bindPoint, colorAndResolveAttachments, preserveAttachments);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
		const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment)
	{
		return _internal.AddSubpassDescriptorWithResolveAttachmentsWithDepth(bindPoint, colorAndResolveAttachments, preserveAttachments, depthAttachment);
	}

}