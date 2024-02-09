#include "../Other/pch.h"
#include "DevicePipelineDataInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "../SharedData/SharedDataPipelineLayoutElementsInternal.h"
#include "../SharedData/SharedDataPipelineElementsInternal.h"

namespace VulkanSimplified
{

	DevicePipelineDataInternal::DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList) : _sharedDataList(sharedDataList),
		_sharedPipelineLayout(_sharedDataList.GetConstSharedDataPipelineLayoutElements())
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

}