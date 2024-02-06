#pragma once

#include "VulkanSimplifierListTemplate.h"

#include "SharedDataSimplifierEnums.h"

struct VkPushConstantRange;

namespace VulkanSimplified
{
	class SharedDataPipelineLayoutElementsInternal;

	class SharedDataPipelineLayoutElements
	{
		SharedDataPipelineLayoutElementsInternal& _internal;

	public:
		SharedDataPipelineLayoutElements(SharedDataPipelineLayoutElementsInternal& ref);
		~SharedDataPipelineLayoutElements();

		SharedDataPipelineLayoutElements(const SharedDataPipelineLayoutElements&) noexcept = delete;

		SharedDataPipelineLayoutElements& operator=(const SharedDataPipelineLayoutElements&) noexcept = delete;

		ListObjectID<VkPushConstantRange> AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size);
	};
}
