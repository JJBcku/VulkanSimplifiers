#pragma once

#include "SharedDataPipelineElementsInternal.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal
	{
		SharedDataPipelineElementsInternal _pipelineData;

	public:
		SharedDataSimplifierCoreInternal(size_t reserve);
		~SharedDataSimplifierCoreInternal();

		SharedDataSimplifierCoreInternal(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataSimplifierCoreInternal& operator=(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& GetSharedDataPipelineElements();
	};
}
