#pragma once

#include "Include/VulkanSimplifierListTemplate.h"


namespace VulkanSimplified
{
	class SharedDataPipelineElementsInternal
	{
		ListTemplate<VkVertexInputBindingDescription> _vertexInputBindingDescriptions;

	public:
		SharedDataPipelineElementsInternal(size_t reserve);
		~SharedDataPipelineElementsInternal();

		SharedDataPipelineElementsInternal(const SharedDataPipelineElementsInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& operator=(const SharedDataPipelineElementsInternal&) noexcept = delete;

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
	};
}
