#include "../Other/pch.h"
#include "DevicePipelineDataInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "../SharedData/SharedDataPipelineLayoutElementsInternal.h"
#include "../SharedData/SharedDataPipelineElementsInternal.h"

namespace VulkanSimplified
{

	DevicePipelineDataInternal::DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList) : _sharedDataList(sharedDataList), _sharedPipelineLayout(_sharedDataList.GetConstSharedDataPipelineLayoutElements())
	{
		_device = device;
		_ppadding = nullptr;
	}

	DevicePipelineDataInternal::~DevicePipelineDataInternal()
	{
	}

	ListObjectID<AutoCleanupDescriptorSetLayout> DevicePipelineDataInternal::AddDescriptorSetLayout(const std::vector<BindingIDsOptional>& bindingsIDList)
	{
		VkDescriptorSetLayoutCreateInfo createInfo{};
		VkDescriptorSetLayout add = VK_NULL_HANDLE;

		if (bindingsIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DevicePipelineDataInternal::AddDescriptorSetLayout Error: binding list overflow!");

		std::vector<VkDescriptorSetLayoutBinding> bindingList;
		bindingList.reserve(bindingsIDList.size());

		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		
		if (!bindingsIDList.empty())
		{
			for (auto& optionalID : bindingsIDList)
			{
				if (optionalID.has_value())
				{
					bindingList.push_back(_sharedPipelineLayout.GetDescriptorSetLayoutBinding(optionalID.value()));
				}
				else
				{
					bindingList.push_back(static_cast<VkDescriptorSetLayoutBinding>(VK_NULL_HANDLE));
				}
			}

			createInfo.bindingCount = static_cast<uint32_t>(bindingsIDList.size());
			createInfo.pBindings = bindingList.data();
		}

		if (vkCreateDescriptorSetLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DevicePipelineDataInternal::AddDescriptorSetLayout Error: Program failed to create a descriptor set layout!");

		return _descriptorSetLayouts.AddObject(AutoCleanupDescriptorSetLayout(_device, add));
	}

	AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout)
	{
		_device = device;
		_descriptorSetLayout = descriptorSetLayout;
	}

	AutoCleanupDescriptorSetLayout::~AutoCleanupDescriptorSetLayout()
	{
		if (_descriptorSetLayout != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorSetLayout(_device, _descriptorSetLayout, nullptr);
		}
	}

	AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& other) noexcept : _device(other._device), _descriptorSetLayout(other._descriptorSetLayout)
	{
		other._device = VK_NULL_HANDLE;
		other._descriptorSetLayout = VK_NULL_HANDLE;
	}

	AutoCleanupDescriptorSetLayout& AutoCleanupDescriptorSetLayout::operator=(AutoCleanupDescriptorSetLayout&& other) noexcept
	{
		_device = other._device;
		_descriptorSetLayout = other._descriptorSetLayout;

		other._device = VK_NULL_HANDLE;
		other._descriptorSetLayout = VK_NULL_HANDLE;

		return *this;
	}

}