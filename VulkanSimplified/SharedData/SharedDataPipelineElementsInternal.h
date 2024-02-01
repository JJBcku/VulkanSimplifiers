#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{
	class SharedDataPipelineElementsInternal
	{
		ListTemplate<VkVertexInputBindingDescription> _vertexInputBindingDescriptions;
		ListTemplate<VkVertexInputAttributeDescription> _vertexInputAttributeDescriptions;

	public:
		SharedDataPipelineElementsInternal(size_t reserve);
		~SharedDataPipelineElementsInternal();

		SharedDataPipelineElementsInternal(const SharedDataPipelineElementsInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& operator=(const SharedDataPipelineElementsInternal&) noexcept = delete;

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);
	};
}
