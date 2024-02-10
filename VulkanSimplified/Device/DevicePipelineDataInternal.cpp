#include "../Other/pch.h"
#include "DevicePipelineDataInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "../SharedData/SharedDataPipelineLayoutElementsInternal.h"
#include "../SharedData/SharedDataPipelineElementsInternal.h"
#include "../SharedData/SharedDataRenderPassElementsInternal.h"

#include "ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{

	DevicePipelineDataInternal::DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList, const ShaderModulesSimplifierInternal& deviceShaderList) :
		_sharedPipelineLayout(sharedDataList.GetConstSharedDataPipelineLayoutElements()), _sharedPipelineData(sharedDataList.GetConstSharedDataPipelineElements()),
		_sharedRenderPass(sharedDataList.GetSharedDataRenderPassElements()), _deviceShaderList(deviceShaderList)
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

	std::vector<ListObjectID<AutoCleanupGraphicsPipeline>> DevicePipelineDataInternal::AddGraphicsPipelines(const std::vector<GraphicsPipelineCreateInfoList>& graphicsPipelinesDataLists)
	{
		std::vector<ListObjectID<AutoCleanupGraphicsPipeline>> ret;
		if (graphicsPipelinesDataLists.empty())
			throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: Function was given no pipelines creation data!");

		if (graphicsPipelinesDataLists.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: graphic pipelines creation data list overflowed!");

		std::vector<VkGraphicsPipelineCreateInfo> _createInfosList;

		std::vector<std::vector<VkPipelineShaderStageCreateInfo>> _shaderInfoList;

		std::vector<std::vector<VkVertexInputBindingDescription>> _vertexInputBindingsList;
		std::vector<std::vector<VkVertexInputAttributeDescription>> _vertexInputAttributesList;
		std::vector<VkPipelineVertexInputStateCreateInfo> _vertexInputStatesList;

		std::vector<VkPipelineInputAssemblyStateCreateInfo> _inputAssemblyStatesList;

		std::vector<VkPipelineViewportStateCreateInfo> _pipelineViewportStatesList;
		std::vector<std::vector<VkViewport>> _pipelineViewportList;
		std::vector<std::vector<VkRect2D>> _pipelineViewportScissorsList;

		std::vector<VkPipelineRasterizationStateCreateInfo> _pipelineRasterizationStatesList;
		std::vector<VkPipelineMultisampleStateCreateInfo> _pipelineMultisamplingStatesList;
		std::vector<VkPipelineDepthStencilStateCreateInfo> _pipelineDepthStencilStatesList;

		std::vector<VkPipelineColorBlendStateCreateInfo> _pipelineColorBlendStatesList;
		std::vector<std::vector<VkPipelineColorBlendAttachmentState>> _pipelineColorBlendAttachmentsList;

		_createInfosList.reserve(graphicsPipelinesDataLists.size());
		_vertexInputStatesList.reserve(graphicsPipelinesDataLists.size());
		_inputAssemblyStatesList.reserve(graphicsPipelinesDataLists.size());
		_pipelineViewportStatesList.reserve(graphicsPipelinesDataLists.size());
		_pipelineRasterizationStatesList.reserve(graphicsPipelinesDataLists.size());
		_pipelineMultisamplingStatesList.reserve(graphicsPipelinesDataLists.size());
		_pipelineDepthStencilStatesList.reserve(graphicsPipelinesDataLists.size());
		_pipelineColorBlendStatesList.reserve(graphicsPipelinesDataLists.size());

		_shaderInfoList.resize(graphicsPipelinesDataLists.size());
		_vertexInputBindingsList.resize(graphicsPipelinesDataLists.size());
		_vertexInputAttributesList.resize(graphicsPipelinesDataLists.size());
		_pipelineViewportList.resize(graphicsPipelinesDataLists.size());
		_pipelineViewportScissorsList.resize(graphicsPipelinesDataLists.size());
		_pipelineColorBlendAttachmentsList.resize(graphicsPipelinesDataLists.size());

		for (size_t i = 0; i < graphicsPipelinesDataLists.size(); ++i)
		{
			VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
			pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

			auto& pipelineData = graphicsPipelinesDataLists[i];

			if (pipelineData._shaderStagesDataList.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: shader stages data list overflowed!");

			_shaderInfoList[i].reserve(pipelineData._shaderStagesDataList.size());

			for (size_t j = 0; j < pipelineData._shaderStagesDataList.size(); ++j)
			{
				auto& shaderData = pipelineData._shaderStagesDataList[j];

				auto shaderStageData = _sharedPipelineData.GetShaderStageCreationData(shaderData.second);

				VkPipelineShaderStageCreateInfo add{};
				add.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				add.module = _deviceShaderList.GetShaderModule(shaderData.first);
				add.pName = shaderStageData._name;

				switch (shaderStageData._stage)
				{
				case VulkanSimplified::ShaderStageType::VERTEX:
					add.stage = VK_SHADER_STAGE_VERTEX_BIT;
					break;
				case VulkanSimplified::ShaderStageType::FRAGMENT:
					add.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
					break;
				default:
					break;
				}

				_shaderInfoList[i].push_back(add);
			}

			pipelineCreateInfo.stageCount = static_cast<uint32_t>(_shaderInfoList[i].size());
			pipelineCreateInfo.pStages = _shaderInfoList[i].data();

			{
				auto vertexInputDataList = _sharedPipelineData.GetVertexInputList(pipelineData._vertexInput);

				if (vertexInputDataList._bindings.size() > std::numeric_limits<uint32_t>::max())
					throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: vertex input bindings data list overflowed!");

				if (vertexInputDataList._attributes.size() > std::numeric_limits<uint32_t>::max())
					throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: vertex input attributes data list overflowed!");

				VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo{};
				vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

				if (!vertexInputDataList._bindings.empty())
				{
					_vertexInputBindingsList[i] = _sharedPipelineData.GetVertexInputBindingDescriptionsList(vertexInputDataList._bindings);

					vertexInputCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputDataList._bindings.size());
					vertexInputCreateInfo.pVertexBindingDescriptions = _vertexInputBindingsList[i].data();
				}

				if (!vertexInputDataList._attributes.empty())
				{
					_vertexInputAttributesList[i] = _sharedPipelineData.GetVertexInputAttributeDescriptionsList(vertexInputDataList._attributes);

					vertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputDataList._attributes.size());
					vertexInputCreateInfo.pVertexAttributeDescriptions = _vertexInputAttributesList[i].data();
				}

				_vertexInputStatesList.push_back(vertexInputCreateInfo);
				pipelineCreateInfo.pVertexInputState = &_vertexInputStatesList.back();
			}

			{
				_inputAssemblyStatesList.push_back(_sharedPipelineData.GetInputAssemblyState(pipelineData._inputAssembly));

				pipelineCreateInfo.pInputAssemblyState = &_inputAssemblyStatesList.back();
			}

			{
				auto viewportData = _sharedPipelineData.GetPipelineViewportsStateList(pipelineData._viewportState);

				VkPipelineViewportStateCreateInfo viewportCreateInfo{};
				viewportCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

				if (!viewportData._viewportScissorPairs.empty())
				{
					if (viewportData._viewportScissorPairs.size() > std::numeric_limits<uint32_t>::max())
						throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: viewport and scissor pair list overflowed!");

					_pipelineViewportList[i].reserve(viewportData._viewportScissorPairs.size());
					_pipelineViewportScissorsList[i].reserve(viewportData._viewportScissorPairs.size());

					for (size_t j = 0; j < viewportData._viewportScissorPairs.size(); ++j)
					{
						_pipelineViewportList[i].push_back(_sharedPipelineData.GetViewport(viewportData._viewportScissorPairs[j].first));
						_pipelineViewportScissorsList[i].push_back(_sharedPipelineData.GetScissors(viewportData._viewportScissorPairs[j].second));
					}

					viewportCreateInfo.viewportCount = static_cast<uint32_t>(viewportData._viewportScissorPairs.size());
					viewportCreateInfo.scissorCount = static_cast<uint32_t>(viewportData._viewportScissorPairs.size());

					viewportCreateInfo.pViewports = _pipelineViewportList[i].data();
					viewportCreateInfo.pScissors = _pipelineViewportScissorsList[i].data();
				}

				_pipelineViewportStatesList.push_back(viewportCreateInfo);
				pipelineCreateInfo.pViewportState = &_pipelineViewportStatesList.back();
			}

			{
				_pipelineRasterizationStatesList.push_back(_sharedPipelineData.GetPipelineRasterizationState(pipelineData._rasterizationState));
				pipelineCreateInfo.pRasterizationState = &_pipelineRasterizationStatesList.back();

				_pipelineMultisamplingStatesList.push_back(_sharedPipelineData.GetPipelineMultisampleState(pipelineData._multisamplingState));
				pipelineCreateInfo.pMultisampleState = &_pipelineMultisamplingStatesList.back();

				if (pipelineData._depthStencilState.has_value())
				{
					_pipelineDepthStencilStatesList.push_back(_sharedPipelineData.GetPipelineDepthStencilState(pipelineData._depthStencilState.value()));
					pipelineCreateInfo.pDepthStencilState = &_pipelineDepthStencilStatesList.back();
				}
			}

			{
				auto colorBlendingData = _sharedPipelineData.GetColorBlendSettings(pipelineData._colorBlendState);
				
				if (colorBlendingData._attachments.size() > std::numeric_limits<uint32_t>::max())
					throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: color blending attachments list overflowed!");

				VkPipelineColorBlendStateCreateInfo colorBlendCreateInfo{};
				colorBlendCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				colorBlendCreateInfo.blendConstants[0] = colorBlendingData._blendConstantR;
				colorBlendCreateInfo.blendConstants[1] = colorBlendingData._blendConstantG;
				colorBlendCreateInfo.blendConstants[2] = colorBlendingData._blendConstantB;
				colorBlendCreateInfo.blendConstants[3] = colorBlendingData._blendConstantA;

				if (!colorBlendingData._attachments.empty())
				{
					_pipelineColorBlendAttachmentsList[i] = _sharedPipelineData.GetPipelineColorBlendAttachmentStatesList(colorBlendingData._attachments);

					colorBlendCreateInfo.attachmentCount = static_cast<uint32_t>(colorBlendingData._attachments.size());
					colorBlendCreateInfo.pAttachments = _pipelineColorBlendAttachmentsList[i].data();
				}

				_pipelineColorBlendStatesList.push_back(colorBlendCreateInfo);
				pipelineCreateInfo.pColorBlendState = &_pipelineColorBlendStatesList.back();
			}

			{
				pipelineCreateInfo.layout = GetPipelineLayout(pipelineData._pipelineLayout);
				pipelineCreateInfo.renderPass = GetRenderPass(pipelineData._renderPass);
				pipelineCreateInfo.subpass = pipelineData._subpass;
			}

			{
				pipelineCreateInfo.basePipelineIndex = -1;
				pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

				if (pipelineData._basePipelineID._idType != VulkanSimplified::BasePipelineIDType::NONE)
				{
					if (pipelineData._basePipelineID._idType == VulkanSimplified::BasePipelineIDType::ALREADY_CREATED)
					{
						pipelineCreateInfo.basePipelineHandle = GetGraphicsPipeline(pipelineData._basePipelineID._outsideID._basePipelineOutsideID);
					}
					else
					{
						size_t baseId = pipelineData._basePipelineID._insideID._basePipelineCurrentListID;

						if (baseId >= std::numeric_limits<uint32_t>::max())
							throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: base pipeline inside ID overflow!");

						if (baseId >= graphicsPipelinesDataLists.size())
							throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: base pipeline inside ID points outside the pipeline list!");

						if (baseId >= i)
							throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: base pipeline inside ID must point to an pipeline placed before this one in the list!");

						pipelineCreateInfo.basePipelineIndex = static_cast<int32_t>(baseId);
					}
				}
			}

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
			pipelineCreateInfo.flags |= VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;
#endif

			if (pipelineData._allowDerivatives)
				pipelineCreateInfo.flags |= VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;

			_createInfosList.push_back(pipelineCreateInfo);
		}

		std::vector<VkPipeline> output;
		output.resize(graphicsPipelinesDataLists.size());

		if (vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, static_cast<uint32_t>(_createInfosList.size()), _createInfosList.data(), nullptr, output.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("DevicePipelineDataInternal::AddGraphicsPipelines Error: Program failed to create the graphic pipelines!");
		}

		ret.reserve(output.size());
		for (auto& pipeline : output)
		{
			ret.emplace_back(_graphicsPipelines.AddObject(AutoCleanupGraphicsPipeline(_device, pipeline)));
		}

		return ret;
	}

	VkPipelineLayout DevicePipelineDataInternal::GetPipelineLayout(ListObjectID<AutoCleanupPipelineLayout> pipelineLayoutID) const
	{
		return _pipelineLayouts.GetConstObject(pipelineLayoutID).GetPipelineLayout();
	}

	VkRenderPass DevicePipelineDataInternal::GetRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID) const
	{
		return _renderPasses.GetConstObject(renderPassID).GetRenderPass();
	}

	VkPipeline DevicePipelineDataInternal::GetGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID) const
	{
		return _graphicsPipelines.GetConstObject(graphicsPipelineID).GetGraphicsPipeline();
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

	VkPipelineLayout AutoCleanupPipelineLayout::GetPipelineLayout() const
	{
		return _pipelineLayout;
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

	VkRenderPass AutoCleanupRenderPass::GetRenderPass() const
	{
		return _renderPass;
	}

	AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline) : _device(device), _ppadding(nullptr), _pipeline(pipeline)
	{
	}

	AutoCleanupGraphicsPipeline::~AutoCleanupGraphicsPipeline()
	{
		if (_pipeline != VK_NULL_HANDLE)
			vkDestroyPipeline(_device, _pipeline, nullptr);
	}

	AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& other) noexcept : _device(other._device), _ppadding(nullptr), _pipeline(other._pipeline)
	{
		other._device = VK_NULL_HANDLE;
		other._pipeline = VK_NULL_HANDLE;
	}

	AutoCleanupGraphicsPipeline& AutoCleanupGraphicsPipeline::operator=(AutoCleanupGraphicsPipeline&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_pipeline = other._pipeline;

		other._device = VK_NULL_HANDLE;
		other._pipeline = VK_NULL_HANDLE;

		return *this;
	}

	VkPipeline AutoCleanupGraphicsPipeline::GetGraphicsPipeline() const
	{
		return _pipeline;
	}

}