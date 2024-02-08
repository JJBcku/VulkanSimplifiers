#pragma once

#include "SharedDataPipelineElementsInternal.h"
#include "SharedDataPipelineLayoutElementsInternal.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal
	{
		SharedDataPipelineElementsInternal _pipelineData;
		SharedDataPipelineLayoutElementsInternal _pipelineLayoutData;

	public:
		SharedDataSimplifierCoreInternal(size_t reserve);
		~SharedDataSimplifierCoreInternal();

		SharedDataSimplifierCoreInternal(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataSimplifierCoreInternal& operator=(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& GetSharedDataPipelineElements();
		SharedDataPipelineLayoutElementsInternal& GetSharedDataPipelineLayoutElements();

		const SharedDataPipelineElementsInternal& GetConstSharedDataPipelineElements() const;
		const SharedDataPipelineLayoutElementsInternal& GetConstSharedDataPipelineLayoutElements() const;
	};
}
