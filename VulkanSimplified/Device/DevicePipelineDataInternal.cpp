#include "../Other/pch.h"
#include "DevicePipelineDataInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "../SharedData/SharedDataPipelineLayoutElementsInternal.h"
#include "../SharedData/SharedDataPipelineElementsInternal.h"
#include "../SharedData/SharedDataRenderPassElementsInternal.h"

namespace VulkanSimplified
{

	DevicePipelineDataInternal::DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList) :
		_sharedPipelineLayout(sharedDataList.GetConstSharedDataPipelineLayoutElements()), _sharedRenderPass(sharedDataList.GetSharedDataRenderPassElements())
	{
		_device = device;
		_ppadding = nullptr;
	}

	DevicePipelineDataInternal::~DevicePipelineDataInternal()
	{
	}

	ListObjectID<AutoCleanupDescriptorSetLayout> DevicePipelineDataInternal::AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList)
	{
		VkDescriptorSetLayoutCreateInfo createInfo{};
		VkDescriptorSetLayout add = VK_NULL_HANDLE;

		if (bindingsIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddDescriptorSetLayout Error: binding list overflow!");

		std::vector<VkDescriptorSetLayoutBinding> bindingList;

		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		
		if (!bindingsIDList.empty())
		{
			bindingList = _sharedPipelineLayout.GetDescriptorSetLayoutBindingsList(bindingsIDList);

			createInfo.bindingCount = static_cast<uint32_t>(bindingsIDList.size());
			createInfo.pBindings = bindingList.data();
		}

		if (vkCreateDescriptorSetLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DevicePipelineDataInternal::AddDescriptorSetLayout Error: Program failed to create a descriptor set layout!");

		return _descriptorSetLayouts.AddObject(AutoCleanupDescriptorSetLayout(_device, add));
	}

	ListObjectID<AutoCleanupPipelineLayout> DevicePipelineDataInternal::AddPipelineLayout
	(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts, const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges)
	{
		std::vector<VkDescriptorSetLayout> _descriptorLayouts;
		std::vector<VkPushConstantRange> _pushConstants;

		if (descriptorSetLayouts.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddPipelineLayout Error: Program was given too much descriptor layout sets IDs!");

		if (pushConstantRanges.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddPipelineLayout Error: Program was given too much push constant renges IDs!");

		VkPipelineLayoutCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		if (!descriptorSetLayouts.empty())
		{
			_descriptorLayouts.reserve(descriptorSetLayouts.size());

			for (auto& descriptor : descriptorSetLayouts)
			{
				if (descriptor.has_value())
					_descriptorLayouts.push_back(GetDescriptorSetLayout(descriptor.value()));
				else
					_descriptorLayouts.push_back(VK_NULL_HANDLE);
			}

			createInfo.setLayoutCount = static_cast<uint32_t>(_descriptorLayouts.size());
			createInfo.pSetLayouts = _descriptorLayouts.data();
		}

		if (!pushConstantRanges.empty())
		{
			_pushConstants = _sharedPipelineLayout.GetPushConstantsRangesList(pushConstantRanges);

			createInfo.pushConstantRangeCount = static_cast<uint32_t>(_pushConstants.size());
			createInfo.pPushConstantRanges = _pushConstants.data();
		}

		VkPipelineLayout add = VK_NULL_HANDLE;

		if (vkCreatePipelineLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DevicePipelineDataInternal::AddPipelineLayout Error: Program failed to create the pipeline layout!");


		return _pipelineLayouts.AddObject(AutoCleanupPipelineLayout(_device, add));
	}

	VkDescriptorSetLayout DevicePipelineDataInternal::GetDescriptorSetLayout(ListObjectID<AutoCleanupDescriptorSetLayout> descriptorID) const
	{
		return _descriptorSetLayouts.GetConstObject(descriptorID).GetDescriptorSetLayout();
	}

	ListObjectID<AutoCleanupRenderPass> DevicePipelineDataInternal::AddRenderPass(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptors,
		const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptions, const std::vector<ListObjectID<VkSubpassDependency>>& subpassDependencies)
	{
		if (attachmentDescriptors.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: attachment descriptors list size overflowed!");

		if (subpassDescriptions.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: subpass descriptors list size overflowed!");

		if (subpassDependencies.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: subpass dependencies list size overflowed!");

		VkRenderPassCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		std::vector<VkAttachmentDescription> attachments;

		if (!attachmentDescriptors.empty())
		{
			attachments = _sharedRenderPass.GetAttachmentDescriptionsList(attachmentDescriptors);

			createInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			createInfo.pAttachments = attachments.data();
		}

		auto subpassData = _sharedRenderPass.GetSubpassDescriptionsDataList(subpassDescriptions);
		std::vector<VkSubpassDescription> finalSubpassDescriptions;
		std::vector<std::vector<VkAttachmentReference>> inputAttachments;
		std::vector<std::vector<VkAttachmentReference>> colorAttachments;
		std::vector<std::vector<VkAttachmentReference>> resolveAttachments;
		std::vector<std::vector<uint32_t>> preserveAttachments;
		std::vector<std::optional<VkAttachmentReference>> depthAttachments;

		finalSubpassDescriptions.reserve(subpassData.size());
		inputAttachments.resize(subpassData.size());
		colorAttachments.resize(subpassData.size());
		resolveAttachments.resize(subpassData.size());
		preserveAttachments.resize(subpassData.size());
		depthAttachments.resize(subpassData.size());

		for (size_t i = 0; i < subpassData.size(); ++i)
		{
			if (subpassData[i]._inputAttachments.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: input attachment list size overflowed!");

			if (subpassData[i]._colorAttachments.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: color attachment list size overflowed!");

			if (subpassData[i]._resolveAttachments.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: resolve attachment list size overflowed!");

			if (subpassData[i]._preserveAttachments.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: preserve attachment list size overflowed!");

			if (subpassData[i]._preserveAttachments.size() != 0 && subpassData[i]._preserveAttachments.size() != subpassData[i]._colorAttachments.size())
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: resolve attachments have to be specified for all color attachments or none!");

			VkSubpassDescription singleDescription{};
			
			switch (subpassData[i]._bindPoint)
			{
			case VulkanSimplified::PipelineBindPoint::COMPUTE:
				singleDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
				break;
			case VulkanSimplified::PipelineBindPoint::GRAPHIC:
				singleDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				break;
			default:
				throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: Program was given an erroneous pipeline bind point value!");
			}

			if (!subpassData[i]._inputAttachments.empty())
			{
				inputAttachments[i] = _sharedRenderPass.GetAttachmentReferencesList(subpassData[i]._inputAttachments);

				singleDescription.inputAttachmentCount = static_cast<uint32_t>(subpassData[i]._inputAttachments.size());
				singleDescription.pInputAttachments = inputAttachments[i].data();
			}

			if (!subpassData[i]._colorAttachments.empty())
			{
				colorAttachments[i] = _sharedRenderPass.GetAttachmentReferencesList(subpassData[i]._colorAttachments);

				singleDescription.colorAttachmentCount = static_cast<uint32_t>(subpassData[i]._colorAttachments.size());
				singleDescription.pColorAttachments = colorAttachments[i].data();
			}

			if (!subpassData[i]._resolveAttachments.empty())
			{
				resolveAttachments[i] = _sharedRenderPass.GetAttachmentReferencesList(subpassData[i]._resolveAttachments);

				singleDescription.pResolveAttachments = resolveAttachments[i].data();
			}

			if (!subpassData[i]._preserveAttachments.empty())
			{
				auto tempAttachments = _sharedRenderPass.GetAttachmentReferencesList(subpassData[i]._preserveAttachments);
				preserveAttachments[i].reserve(tempAttachments.size());

				for (auto& attachment : tempAttachments)
				{
					preserveAttachments[i].push_back(attachment.attachment);
				}

				singleDescription.preserveAttachmentCount = static_cast<uint32_t>(subpassData[i]._preserveAttachments.size());
				singleDescription.pPreserveAttachments = preserveAttachments[i].data();
			}

			if (subpassData[i]._depthAttachment.has_value())
			{
				depthAttachments[i] = _sharedRenderPass.GetAttachmentReference(subpassData[i]._depthAttachment.value());
				singleDescription.pDepthStencilAttachment = &depthAttachments[i].value();
			}

			finalSubpassDescriptions.push_back(singleDescription);
		}

		if (!finalSubpassDescriptions.empty())
		{
			createInfo.subpassCount = static_cast<uint32_t>(finalSubpassDescriptions.size());
			createInfo.pSubpasses = finalSubpassDescriptions.data();
		}

		std::vector<VkSubpassDependency> dependencies;

		if (!subpassDependencies.empty())
		{
			dependencies = _sharedRenderPass.GetSubpassDependenciesList(subpassDependencies);

			createInfo.subpassCount = static_cast<uint32_t>(dependencies.size());
			createInfo.pDependencies = dependencies.data();
		}

		VkRenderPass add = VK_NULL_HANDLE;

		if (vkCreateRenderPass(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DevicePipelineDataInternal::AddRenderPass Error: Program failed to create a render pass!");

		return _renderPasses.AddObject(AutoCleanupRenderPass(_device, add));
	}

	AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout)
	{
		_device = device;
		_ppadding = nullptr;
		_descriptorSetLayout = descriptorSetLayout;
	}

	AutoCleanupDescriptorSetLayout::~AutoCleanupDescriptorSetLayout()
	{
		if (_descriptorSetLayout != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorSetLayout(_device, _descriptorSetLayout, nullptr);
		}
	}

	AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& other) noexcept : _device(other._device),
		_descriptorSetLayout(other._descriptorSetLayout)
	{
		_ppadding = nullptr;

		other._device = VK_NULL_HANDLE;
		other._descriptorSetLayout = VK_NULL_HANDLE;
	}

	AutoCleanupDescriptorSetLayout& AutoCleanupDescriptorSetLayout::operator=(AutoCleanupDescriptorSetLayout&& other) noexcept
	{
		_device = other._device;
		_descriptorSetLayout = other._descriptorSetLayout;
		_ppadding = nullptr;

		other._device = VK_NULL_HANDLE;
		other._descriptorSetLayout = VK_NULL_HANDLE;

		return *this;
	}

	VkDescriptorSetLayout AutoCleanupDescriptorSetLayout::GetDescriptorSetLayout() const
	{
		return _descriptorSetLayout;
	}

	AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout) : _device(device), _pipelineLayout(pipelineLayout)
	{
		_ppadding = nullptr;
	}

	AutoCleanupPipelineLayout::~AutoCleanupPipelineLayout()
	{
		if (_pipelineLayout != VK_NULL_HANDLE)
		{
			vkDestroyPipelineLayout(_device, _pipelineLayout, nullptr);
		}
	}

	AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& other) noexcept : _device(other._device), _pipelineLayout(other._pipelineLayout)
	{
		_ppadding = nullptr;

		other._device = VK_NULL_HANDLE;
		other._pipelineLayout = VK_NULL_HANDLE;
	}

	AutoCleanupPipelineLayout& AutoCleanupPipelineLayout::operator=(AutoCleanupPipelineLayout&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_pipelineLayout = other._pipelineLayout;

		other._device = VK_NULL_HANDLE;
		other._pipelineLayout = VK_NULL_HANDLE;

		return *this;
	}

	AutoCleanupRenderPass::AutoCleanupRenderPass(VkDevice device, VkRenderPass renderPass) : _device(device), _ppadding(nullptr), _renderPass(renderPass)
	{
	}

	AutoCleanupRenderPass::~AutoCleanupRenderPass()
	{
		if (_renderPass != VK_NULL_HANDLE)
			vkDestroyRenderPass(_device, _renderPass, nullptr);
	}

	AutoCleanupRenderPass::AutoCleanupRenderPass(AutoCleanupRenderPass&& other) noexcept : _device(other._device), _renderPass(other._renderPass)
	{
		_ppadding = nullptr;

		other._device = VK_NULL_HANDLE;
		other._renderPass = VK_NULL_HANDLE;
	}

	AutoCleanupRenderPass& AutoCleanupRenderPass::operator=(AutoCleanupRenderPass&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_renderPass = other._renderPass;

		other._device = VK_NULL_HANDLE;
		other._renderPass = VK_NULL_HANDLE;

		return *this;
	}

}