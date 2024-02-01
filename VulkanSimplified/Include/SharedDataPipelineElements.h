#pragma once

#include "VulkanSimplifierListTemplate.h"
#include "SharedDataSimplifierEnums.h"

struct VkVertexInputBindingDescription;
struct VkVertexInputAttributeDescription;

namespace VulkanSimplified
{
	class SharedDataPipelineElementsInternal;

	struct VertexInputList;

	class SharedDataPipelineElements
	{
		SharedDataPipelineElementsInternal& _internal;

	public:
		SharedDataPipelineElements(SharedDataPipelineElementsInternal& ref);
		~SharedDataPipelineElements();

		SharedDataPipelineElements& operator=(const SharedDataPipelineElements&) noexcept = delete;

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);

		ListObjectID<VertexInputList> AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes);
	};
}

