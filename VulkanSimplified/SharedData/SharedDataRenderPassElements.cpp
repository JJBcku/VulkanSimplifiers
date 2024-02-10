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
		PipelineMultisampleCount sampleCount, AttachmentLoadMode loadMode, AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout)
	{
		return _internal.AddAttachmentDescriptionWithSwapchainsFormat(mayAlias, sampleCount, loadMode, storeMode, initialLayout, finalLayout);
	}

	ListObjectID<VkAttachmentReference> SharedDataRenderPassElements::AddAttachmentReference(uint32_t attachment, AttachmentLayout layout)
	{
		return _internal.AddAttachmentReference(attachment, layout);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		return _internal.AddSubpassDescriptorNoDepth(bindPoint, inputAttachments, colorAttachments, preserveAttachments);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment)
	{
		return _internal.AddSubpassDescriptorWithDepth(bindPoint, inputAttachments, colorAttachments, preserveAttachments, depthAttachment);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
		const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		return _internal.AddSubpassDescriptorWithResolveAttachmentsNoDepth(bindPoint, inputAttachments, colorAndResolveAttachments, preserveAttachments);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElements::AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& inputAttachments,
		const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment)
	{
		return _internal.AddSubpassDescriptorWithResolveAttachmentsWithDepth(bindPoint, inputAttachments, colorAndResolveAttachments, preserveAttachments, depthAttachment);
	}

	ListObjectID<VkSubpassDependency> SharedDataRenderPassElements::AddSubpassDependency(std::optional<uint32_t> srcSubpass, std::optional<uint32_t> dstSubpass, PipelineStage srcStageMask, PipelineStage dstStageMask, PipelineAccess srcAccessMask, PipelineAccess dstAccessMask)
	{
		return _internal.AddSubpassDependency(srcSubpass, dstSubpass, srcStageMask, dstStageMask, srcAccessMask, dstAccessMask);
	}

}