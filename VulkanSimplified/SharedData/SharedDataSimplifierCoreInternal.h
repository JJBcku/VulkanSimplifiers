#pragma once

#include "SharedDataPipelineElementsInternal.h"
#include "SharedDataPipelineLayoutElementsInternal.h"
#include "SharedDataRenderPassElementsInternal.h"

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;

	class SharedDataSimplifierCoreInternal
	{
		const BasicsSimplifierInternal& _basic;
		void* _ppadding;

		SharedDataPipelineElementsInternal _pipelineData;
		SharedDataPipelineLayoutElementsInternal _pipelineLayoutData;
		SharedDataRenderPassElementsInternal _renderPassData;

	public:
		SharedDataSimplifierCoreInternal(size_t reserve, const BasicsSimplifierInternal& ref);
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
