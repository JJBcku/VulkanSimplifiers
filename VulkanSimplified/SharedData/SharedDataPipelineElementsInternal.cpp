#include "../pch.h"
#include "SharedDataPipelineElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineElementsInternal::SharedDataPipelineElementsInternal(size_t reserve) : _vertexInputBindingDescriptions(reserve)
	{
	}

	SharedDataPipelineElementsInternal::~SharedDataPipelineElementsInternal()
	{
	}

	ListObjectID<VkVertexInputBindingDescription> SharedDataPipelineElementsInternal::AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex)
	{
		VkVertexInputBindingDescription add{};
		add.binding = binding;
		add.stride = stride;
		add.inputRate = useInstanceIndex ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;

		return _vertexInputBindingDescriptions.AddObject(add);
	}

	ListObjectID<VkVertexInputAttributeDescription> SharedDataPipelineElementsInternal::AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset)
	{
		VkVertexInputAttributeDescription add{};
		add.location = location;
		add.binding = binding;
		add.format = VK_FORMAT_MAX_ENUM;
		add.offset = offset;

		switch (format)
		{
		case VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT:
			add.format = VK_FORMAT_R32G32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC2_DOUBLE:
			add.format = VK_FORMAT_R64G64_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT:
			add.format = VK_FORMAT_R32G32B32A32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_DOUBLE:
			add.format = VK_FORMAT_R64G64B64A64_SFLOAT;
			break;
		default:
			throw std::runtime_error("AddAttributeDescription Error: Program used erroneous vertex attribute format!");
		}

		return _vertexInputAttributeDescriptions.AddObject(add);
	}

}
