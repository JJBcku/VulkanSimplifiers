#pragma once

#include "SharedDataPipelineElementsInternal.h"
#include "SharedDataPipelineLayoutElementsInternal.h"
#include "SharedDataRenderPassElementsInternal.h"

namespace VulkanSimplified
{
	class MainSimplifierInternal;

	class SharedDataSimplifierCoreInternal
	{
		const MainSimplifierInternal& _main;
		void* _ppadding;

		SharedDataPipelineElementsInternal _pipelineData;
		SharedDataPipelineLayoutElementsInternal _pipelineLayoutData;
		SharedDataRenderPassElementsInternal _renderPassData;

	public:
		SharedDataSimplifierCoreInternal(size_t reserve, const MainSimplifierInternal& ref);
		~SharedDataSimplifierCoreInternal();

		SharedDataSimplifierCoreInternal(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataSimplifierCoreInternal& operator=(const SharedDataSimplifierCoreInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& GetSharedDataPipelineElements();
		SharedDataPipelineLayoutElementsInternal& GetSharedDataPipelineLayoutElements();
		SharedDataRenderPassElementsInternal& GetSharedDataRenderPassElements();

		const SharedDataPipelineElementsInternal& GetConstSharedDataPipelineElements() const;
		const SharedDataPipelineLayoutElementsInternal& GetConstSharedDataPipelineLayoutElements() const;
		const SharedDataRenderPassElementsInternal& GetSharedDataRenderPassElements() const;
	};
}
