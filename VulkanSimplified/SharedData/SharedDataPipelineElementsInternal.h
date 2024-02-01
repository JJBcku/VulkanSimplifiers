#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{
	struct VertexInputList
	{
		std::vector<ListObjectID<VkVertexInputBindingDescription>> _bindings;
		std::vector<ListObjectID<VkVertexInputAttributeDescription>> _attributes;
	};

	class SharedDataPipelineElementsInternal
	{
		ListTemplate<VkVertexInputBindingDescription> _vertexInputBindingDescriptions;
		ListTemplate<VkVertexInputAttributeDescription> _vertexInputAttributeDescriptions;

		ListTemplate<VertexInputList> _vertexInputListDescriptions;

	public:
		SharedDataPipelineElementsInternal(size_t reserve);
		~SharedDataPipelineElementsInternal();

		SharedDataPipelineElementsInternal(const SharedDataPipelineElementsInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& operator=(const SharedDataPipelineElementsInternal&) noexcept = delete;

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);

		ListObjectID<VertexInputList> AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes);
	};
}
