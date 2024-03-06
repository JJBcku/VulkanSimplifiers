#include "../Other/pch.h"
#include "../Include/Common/Utils.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{

	VkDeviceSize Utils::GetShaderInputPadding(VkDeviceSize currentSize, VertexAttributeFormats attribute)
	{
		VkDeviceSize ret = 0;

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
			throw std::runtime_error("Utils::GetShaderInputPadding Error: Program was given an erroneous value of the attributes type!");
		}

		return ret;
	}

	VkDeviceSize Utils::GetShaderInputPaddedSize(const std::vector<VertexAttributeFormats>& attributes)
	{
		VkDeviceSize ret = 0;

		if (!attributes.empty())
		{
			for (size_t i = 0; i < attributes.size(); ++i)
			{
				ret += GetShaderInputPadding(ret, attributes[i]);

				switch (attributes[i])
				{
				case VertexAttributeFormats::VEC2_FLOAT:
					ret += static_cast<VkDeviceSize>(sizeof(float)) << 1;
					break;
				case VertexAttributeFormats::VEC2_DOUBLE:
					ret += static_cast<VkDeviceSize>(sizeof(double)) << 1;
					break;
				case VertexAttributeFormats::VEC4_FLOAT:
					ret += static_cast<VkDeviceSize>(sizeof(float)) << 2;
					break;
				case VertexAttributeFormats::VEC4_DOUBLE:
					ret += static_cast<VkDeviceSize>(sizeof(double)) << 2;
					break;
				default:
					throw std::runtime_error("Utils::GetShaderInputPaddedSize Error: Program was given an erroneous value of the attributes type!");
				}
			}

			ret += GetShaderInputPadding(ret, attributes[0]);
		}

		return ret;
	}

}