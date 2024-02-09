#pragma once

struct VkVertexInputBindingDescription;

#include "VulkanSimplifierListTemplate.h"
#include "SharedDataPipelineElements.h"
#include "SharedDataPipelineLayoutElements.h"
#include "SharedDataRenderPassElements.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;

	class SharedDataSimplifierCore
	{
		SharedDataSimplifierCoreInternal& _internal;

	public:
		SharedDataSimplifierCore(SharedDataSimplifierCoreInternal& ref);
		~SharedDataSimplifierCore();

		SharedDataSimplifierCore(const SharedDataSimplifierCore&) noexcept = delete;
		
		SharedDataSimplifierCore& operator=(const SharedDataSimplifierCore&) noexcept = delete;

		SharedDataPipelineElements GetSharedDataPipelineElements();
		SharedDataPipelineLayoutElements GetSharedDataPipelineLayoutElements();
		SharedDataRenderPassElements GetSharedDataRenderPassElements();
	};
}


