#include "../Other/pch.h"
#include "../Include/Common/Utils.h"

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

}