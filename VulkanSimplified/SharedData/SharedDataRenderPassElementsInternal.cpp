#include "../Other/pch.h"
#include "SharedDataRenderPassElementsInternal.h"

#include "../Basics/SwapchainSimplifierInternal.h"

#include "../Other/MainSimplifierInternal.h"

namespace VulkanSimplified
{
	VkImageLayout SharedDataRenderPassElementsInternal::GetImageLayout(AttachmentLayout layout)
	{
		VkImageLayout ret = VK_IMAGE_LAYOUT_MAX_ENUM;

		switch (layout)
		{
		case VulkanSimplified::AttachmentLayout::IGNORED:
			ret = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		case VulkanSimplified::AttachmentLayout::PRESENT:
			ret = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case VulkanSimplified::AttachmentLayout::COLOR:
			ret = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		default:
			break;
		}

		return ret;
	}

	SharedDataRenderPassElementsInternal::SharedDataRenderPassElementsInternal(size_t reserve, const MainSimplifierInternal& ref) : _main(ref), _attachmentDescriptions(reserve),
		_attachmentReferences(reserve), _subpassDescriptions(reserve)
	{
		_ppadding = nullptr;
	}

	SharedDataRenderPassElementsInternal::~SharedDataRenderPassElementsInternal()
	{
	}

	ListObjectID<VkAttachmentDescription> SharedDataRenderPassElementsInternal::AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount,
		AttachmentLoadMode loadMode, AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout)
	{
		VkAttachmentDescription add{};
		
		if (mayAlias)
			add.flags = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;

		auto& basics = _main.GetInstanceSimplifier(instanceID);
		auto& swapchain = basics.GetSwapchainSimplifier();

		add.format = swapchain.GetSwapchainFormat();

		switch (sampleCount)
		{
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_1:
			add.samples = VK_SAMPLE_COUNT_1_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_2:
			add.samples = VK_SAMPLE_COUNT_2_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_4:
			add.samples = VK_SAMPLE_COUNT_4_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_8:
			add.samples = VK_SAMPLE_COUNT_8_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_16:
			add.samples = VK_SAMPLE_COUNT_16_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_32:
			add.samples = VK_SAMPLE_COUNT_32_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_64:
			add.samples = VK_SAMPLE_COUNT_64_BIT;
			break;
		default:
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentDescription Error: Program was given an erroneus sample count value!");
		}

		switch (loadMode)
		{
		case VulkanSimplified::AttachmentLoadMode::LOAD:
			add.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			break;
		case VulkanSimplified::AttachmentLoadMode::CLEAR:
			add.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			break;
		case VulkanSimplified::AttachmentLoadMode::IGNORE:
			add.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			break;
		default:
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentDescription Error: Program was given an erroneus load mode value!");
		}

		switch (storeMode)
		{
		case VulkanSimplified::AttachmentStoreMode::STORE:
			add.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			break;
		case VulkanSimplified::AttachmentStoreMode::IGNORE:
			add.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			break;
		default:
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentDescription Error: Program was given an erroneus store mode value!");
		}

		add.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		add.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		add.initialLayout = GetImageLayout(initialLayout);
		add.finalLayout = GetImageLayout(finalLayout);

		if (add.initialLayout == VK_IMAGE_LAYOUT_MAX_ENUM)
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentDescription Error: Program was given an erroneus initial layout value!");

		if (add.finalLayout == VK_IMAGE_LAYOUT_MAX_ENUM)
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentDescription Error: Program was given an erroneus final layout value!");

		return _attachmentDescriptions.AddUniqueObject(add);
	}

	ListObjectID<VkAttachmentReference> SharedDataRenderPassElementsInternal::AddAttachmentReference(uint32_t attachment, AttachmentLayout layout)
	{
		VkAttachmentReference add{};
		add.attachment = attachment;
		add.layout = GetImageLayout(layout);

		if (add.layout == VK_IMAGE_LAYOUT_MAX_ENUM)
			throw std::runtime_error("SharedDataRenderPassElementsInternal::AddAttachmentReference Error: Program was given an erroneous layout variable!");

		return _attachmentReferences.AddUniqueObject(add);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElementsInternal::AddSubpassDescriptorNoDepth(PipelineBindPoint bindPoint, const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		SubpassDescriptionData add;

		add._bindPoint = bindPoint;
		add._colorAttachments = colorAttachments;
		add._preserveAttachments = preserveAttachments;

		return _subpassDescriptions.AddUniqueObject(add);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElementsInternal::AddSubpassDescriptorWithDepth(PipelineBindPoint bindPoint,
		const std::vector<ListObjectID<VkAttachmentReference>>& colorAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments,
		ListObjectID<VkAttachmentReference> depthAttachment)
	{
		SubpassDescriptionData add;

		add._bindPoint = bindPoint;
		add._colorAttachments = colorAttachments;
		add._preserveAttachments = preserveAttachments;
		add._depthAttachment = depthAttachment;

		return _subpassDescriptions.AddUniqueObject(add);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElementsInternal::AddSubpassDescriptorWithResolveAttachmentsNoDepth(PipelineBindPoint bindPoint, const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments, const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments)
	{
		SubpassDescriptionData add;

		add._bindPoint = bindPoint;
		add._preserveAttachments = preserveAttachments;

		add._colorAttachments.reserve(colorAndResolveAttachments.size());
		add._resolveAttachments.reserve(colorAndResolveAttachments.size());

		for (auto& colorAndResolve : colorAndResolveAttachments)
		{
			add._colorAttachments.push_back(colorAndResolve.first);
			add._resolveAttachments.push_back(colorAndResolve.second);
		}

		return _subpassDescriptions.AddUniqueObject(add);
	}

	ListObjectID<SubpassDescriptionData> SharedDataRenderPassElementsInternal::AddSubpassDescriptorWithResolveAttachmentsWithDepth(PipelineBindPoint bindPoint,
		const std::vector<std::pair<ListObjectID<VkAttachmentReference>, ListObjectID<VkAttachmentReference>>>& colorAndResolveAttachments,
		const std::vector<ListObjectID<VkAttachmentReference>>& preserveAttachments, ListObjectID<VkAttachmentReference> depthAttachment)
	{
		SubpassDescriptionData add;

		add._bindPoint = bindPoint;
		add._preserveAttachments = preserveAttachments;
		add._depthAttachment = depthAttachment;

		add._colorAttachments.reserve(colorAndResolveAttachments.size());
		add._resolveAttachments.reserve(colorAndResolveAttachments.size());

		for (auto& colorAndResolve : colorAndResolveAttachments)
		{
			add._colorAttachments.push_back(colorAndResolve.first);
			add._resolveAttachments.push_back(colorAndResolve.second);
		}

		return _subpassDescriptions.AddUniqueObject(add);
	}

}

bool operator==(const VkAttachmentDescription& first, const VkAttachmentDescription& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkAttachmentReference& first, const VkAttachmentReference& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VulkanSimplified::SubpassDescriptionData& first, const VulkanSimplified::SubpassDescriptionData& second) noexcept
{
	if (first._bindPoint != second._bindPoint)
		return false;

	if (first._colorAttachments.size() != second._colorAttachments.size())
		return false;

	if (first._resolveAttachments.size() != second._resolveAttachments.size())
		return false;

	if (first._preserveAttachments.size() != second._preserveAttachments.size())
		return false;

	if (first._depthAttachment.has_value() != second._depthAttachment.has_value())
		return false;

	if (first._depthAttachment.has_value() && first._depthAttachment.value() != second._depthAttachment.value())
		return false;

	for (size_t i = 0; i < first._colorAttachments.size(); ++i)
	{
		if (first._colorAttachments[i] != second._colorAttachments[i])
			return false;
	}

	for (size_t i = 0; i < first._resolveAttachments.size(); ++i)
	{
		if (first._resolveAttachments[i] != second._resolveAttachments[i])
			return false;
	}

	for (size_t i = 0; i < first._preserveAttachments.size(); ++i)
	{
		if (first._preserveAttachments[i] != second._preserveAttachments[i])
			return false;
	}

	return true;
}
