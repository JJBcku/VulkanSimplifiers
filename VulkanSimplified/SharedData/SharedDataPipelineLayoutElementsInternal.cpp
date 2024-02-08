#include "../Other/pch.h"
#include "SharedDataPipelineLayoutElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineLayoutElementsInternal::SharedDataPipelineLayoutElementsInternal(size_t reserve) : _pushConstants(reserve), _descriptorLayoutBindings(reserve)
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

		return _pushConstants.AddUniqueObject(add);
	}

	ListObjectID<VkDescriptorSetLayoutBinding> SharedDataPipelineLayoutElementsInternal::AddDescriptorSetLayoutBinding(uint32_t binding, PipelineLayoutDescriptorType descriptorType, uint32_t descriptorCount, ShaderStageFlags shaderStages)
	{
		VkDescriptorSetLayoutBinding add{};
		add.binding = binding;
		
		switch (descriptorType)
		{
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::COMBINED_SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLED_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineLayoutElementsInternal::AddDescriptorSetLayoutBinding Error: Program was given an erroneous pipeline layout descriptor type!");
		}

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

}

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkDescriptorSetLayoutBinding& first, const VkDescriptorSetLayoutBinding& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}
