#include "../Other/pch.h"
#include "Utils.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{
	VkFormat Utils::GetVertexAttributeFormat(VertexAttributeFormats attribute)
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		switch (attribute)
		{
		case VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT:
			ret = VK_FORMAT_R32G32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC2_DOUBLE:
			ret = VK_FORMAT_R64G64_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT:
			ret = VK_FORMAT_R32G32B32A32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_DOUBLE:
			ret = VK_FORMAT_R64G64B64A64_SFLOAT;
			break;
		default:
			throw std::runtime_error("Utils::GetVertexAttributeFormat Error: Program was given an erroneous input attribute format!");
		}

		return ret;
	}

	uint64_t Utils::GetShaderInputPadding(uint64_t currentSize, VertexAttributeFormats attribute)
	{
		uint64_t ret = 0;

		switch (attribute)
		{
		case VertexAttributeFormats::VEC2_FLOAT:
		case VertexAttributeFormats::VEC4_FLOAT:
			if (currentSize % sizeof(float) != 0)
				ret = sizeof(float) - (currentSize % sizeof(float));
			break;
		case VertexAttributeFormats::VEC2_DOUBLE:
		case VertexAttributeFormats::VEC4_DOUBLE:
			if (currentSize % sizeof(double) != 0)
				ret = sizeof(double) - (currentSize % sizeof(double));
			break;
		default:
			throw std::runtime_error("Utils::GetShaderInputPadding Error: Program was given an erroneous input attribute format!");
		}

		return ret;
	}

	uint64_t Utils::GetShaderInputSize(VertexAttributeFormats attribute)
	{
		uint64_t ret = 0;

		switch (attribute)
		{
		case VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT:
			ret = static_cast<uint64_t>(sizeof(float)) << 1;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC2_DOUBLE:
			ret = static_cast<uint64_t>(sizeof(double)) << 1;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT:
			ret = static_cast<uint64_t>(sizeof(float)) << 2;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_DOUBLE:
			ret = static_cast<uint64_t>(sizeof(double)) << 2;
			break;
		default:
			throw std::runtime_error("Utils::GetShaderInputSize Error: Program was given an erroneous input attribute format!");
		}

		return ret;
	}

	uint32_t Utils::GetAttributeUsedLocationsAmount(VertexAttributeFormats attribute)
	{
		uint32_t ret = 0;

		switch (attribute)
		{
		case VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT:
		case VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT:
			ret = 1;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC2_DOUBLE:
		case VulkanSimplified::VertexAttributeFormats::VEC4_DOUBLE:
			ret = 2;
			break;
		default:
			throw std::runtime_error("Utils::GetAttributeUsedLocationsAmount Error: Program was given an erroneous input attribute format!");
		}

		return ret;
	}

	uint64_t Utils::GetShaderInputPaddedSize(const std::vector<VertexAttributeFormats>& attributes)
	{
		uint64_t ret = 0;

		if (!attributes.empty())
		{
			for (size_t i = 0; i < attributes.size(); ++i)
			{
				ret += GetShaderInputPadding(ret, attributes[i]);

				switch (attributes[i])
				{
				case VertexAttributeFormats::VEC2_FLOAT:
					ret += static_cast<uint64_t>(sizeof(float)) << 1;
					break;
				case VertexAttributeFormats::VEC2_DOUBLE:
					ret += static_cast<uint64_t>(sizeof(double)) << 1;
					break;
				case VertexAttributeFormats::VEC4_FLOAT:
					ret += static_cast<uint64_t>(sizeof(float)) << 2;
					break;
				case VertexAttributeFormats::VEC4_DOUBLE:
					ret += static_cast<uint64_t>(sizeof(double)) << 2;
					break;
				default:
					throw std::runtime_error("Utils::GetShaderInputPaddedSize Error: Program was given an erroneous value of the attributes type!");
				}
			}

			ret += GetShaderInputPadding(ret, attributes[0]);
		}

		return ret;
	}

	std::vector<VkVertexInputAttributeDescription> Utils::CreateAttachmentDescriptors(const std::vector<VertexAttributeFormats>& attributes, uint32_t binding)
	{
		std::vector<VkVertexInputAttributeDescription> ret(attributes.size());

		uint64_t totalSize = 0;
		uint32_t location = 0;

		for (size_t i = 0; i < attributes.size(); ++i)
		{
			totalSize += GetShaderInputPadding(totalSize, attributes[i]);

			ret[i].binding = binding;
			ret[i].format = GetVertexAttributeFormat(attributes[i]);

			ret[i].location = location;
			ret[i].offset = static_cast<uint32_t>(totalSize);

			location += GetAttributeUsedLocationsAmount(attributes[i]);
			totalSize += GetShaderInputSize(attributes[i]);
		}

		return ret;
	}

	VkPipelineStageFlags Utils::TranslatePipelineStage(PipelineStage stages)
	{
		VkPipelineStageFlags ret = VK_PIPELINE_STAGE_NONE;

		if ((stages & PipelineStage::TOP) == PipelineStage::TOP)
			ret |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

		if ((stages & PipelineStage::BOTTOM) == PipelineStage::BOTTOM)
			ret |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		if ((stages & PipelineStage::COLOR_ATTACHMENT_OUTPUT) == PipelineStage::COLOR_ATTACHMENT_OUTPUT)
			ret |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		if ((stages & PipelineStage::VERTEX_INPUT) == PipelineStage::VERTEX_INPUT)
			ret |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;

		if ((stages & PipelineStage::VERTEX_SHADER) == PipelineStage::VERTEX_SHADER)
			ret |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;

		return ret;
	}

	VkDescriptorType Utils::TranslateDescriptorType(PipelineLayoutDescriptorType descriptorType)
	{
		VkDescriptorType ret = VK_DESCRIPTOR_TYPE_MAX_ENUM;

		switch (descriptorType)
		{
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::COMBINED_SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLED_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			break;
		default:
			break;
		}

		return ret;
	}

}