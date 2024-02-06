#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"

#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second);

namespace VulkanSimplified
{
	class SharedDataPipelineLayoutElementsInternal
	{
		ListTemplate<VkPushConstantRange> _pushConstants;

	public:
		SharedDataPipelineLayoutElementsInternal(size_t reserve);
		~SharedDataPipelineLayoutElementsInternal();

		SharedDataPipelineLayoutElementsInternal(const SharedDataPipelineLayoutElementsInternal&) noexcept = delete;
		SharedDataPipelineLayoutElementsInternal(SharedDataPipelineLayoutElementsInternal&&) noexcept = delete;

		SharedDataPipelineLayoutElementsInternal& operator=(const SharedDataPipelineLayoutElementsInternal&) noexcept = delete;
		SharedDataPipelineLayoutElementsInternal& operator=(SharedDataPipelineLayoutElementsInternal&&) noexcept = delete;

		ListObjectID<VkPushConstantRange> AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size);
	};
}
