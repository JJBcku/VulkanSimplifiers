#include "../Other/pch.h"
#include "SharedDataPipelineLayoutElementsInternal.h"

#include "../Other/Utils.h"

namespace VulkanSimplified
{

	SharedDataPipelineLayoutElementsInternal::SharedDataPipelineLayoutElementsInternal(size_t reserve) : _pushConstantRanges(reserve), _descriptorLayoutBindings(reserve)
	{
	}

	SharedDataPipelineLayoutElementsInternal::~SharedDataPipelineLayoutElementsInternal()
	{
	}

	ListObjectID<VkPushConstantRange> SharedDataPipelineLayoutElementsInternal::AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size)
	{
		VkPushConstantRange add{};

		if ((offset & 3) != 0)
			throw std::runtime_error("SharedDataPipelineLayoutElements::AddPushConstantRange: Program was given an offset which is not a multiple of 4!");

		if ((size & 3) != 0)
			throw std::runtime_error("SharedDataPipelineLayoutElements::AddPushConstantRange: Program was given a size which is not a multiple of 4!");

		if (shaderStages != ShaderStageFlags::NONE)
		{
			if ((shaderStages & ShaderStageFlags::VERTEX) == ShaderStageFlags::VERTEX)
				add.stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;

			if ((shaderStages & ShaderStageFlags::FRAGMENT) == ShaderStageFlags::FRAGMENT)
				add.stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
		}

		add.offset = offset;
		add.size = size;

		return _pushConstantRanges.AddUniqueObject(add);
	}

	ListObjectID<VkDescriptorSetLayoutBinding> SharedDataPipelineLayoutElementsInternal::AddDescriptorSetLayoutBinding(uint32_t binding, PipelineLayoutDescriptorType descriptorType, uint32_t descriptorCount, ShaderStageFlags shaderStages)
	{
		VkDescriptorSetLayoutBinding add{};
		add.binding = binding;
		add.descriptorType = Utils::TranslateDescriptorType(descriptorType);

		if (add.descriptorType == VK_DESCRIPTOR_TYPE_MAX_ENUM)
			throw std::runtime_error("SharedDataPipelineLayoutElementsInternal::AddDescriptorSetLayoutBinding Error: Program was given an erroneous pipeline layout descriptor type!");
		

		add.descriptorCount = descriptorCount;

		if (shaderStages != ShaderStageFlags::NONE)
		{
			if ((shaderStages & ShaderStageFlags::VERTEX) == ShaderStageFlags::VERTEX)
				add.stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;

			if ((shaderStages & ShaderStageFlags::FRAGMENT) == ShaderStageFlags::FRAGMENT)
				add.stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
		}

		return _descriptorLayoutBindings.AddUniqueObject(add);
	}

	VkDescriptorSetLayoutBinding SharedDataPipelineLayoutElementsInternal::GetDescriptorSetLayoutBinding(ListObjectID<VkDescriptorSetLayoutBinding> bindingID) const
	{
		return _descriptorLayoutBindings.GetObjectCopy(bindingID);
	}

	std::vector<VkDescriptorSetLayoutBinding> SharedDataPipelineLayoutElementsInternal::GetDescriptorSetLayoutBindingsList(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingIDs) const
	{
		return _descriptorLayoutBindings.GetObjectListCopy(bindingIDs);
	}

	VkPushConstantRange SharedDataPipelineLayoutElementsInternal::GetPushConstantsRange(ListObjectID<VkPushConstantRange> pushConstantsID) const
	{
		return _pushConstantRanges.GetObjectCopy(pushConstantsID);
	}

	std::vector<VkPushConstantRange> SharedDataPipelineLayoutElementsInternal::GetPushConstantsRangesList(const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantsIDs) const
	{
		return _pushConstantRanges.GetObjectListCopy(pushConstantsIDs);
	}

}

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkDescriptorSetLayoutBinding& first, const VkDescriptorSetLayoutBinding& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}
