#include "../Other/pch.h"
#include "SharedDataSimplifierCoreInternal.h"

#include "../Other/MainSimplifierInternal.h"

namespace VulkanSimplified
{

	SharedDataSimplifierCoreInternal::SharedDataSimplifierCoreInternal(size_t reserve, const MainSimplifierInternal& ref) : _main(ref), _pipelineData(reserve),
		_pipelineLayoutData(reserve), _renderPassData(reserve, ref)
	{
		_ppadding = nullptr;
	}

	SharedDataSimplifierCoreInternal::~SharedDataSimplifierCoreInternal()
	{
	}

	SharedDataPipelineElementsInternal& SharedDataSimplifierCoreInternal::GetSharedDataPipelineElements()
	{
		return _pipelineData;
	}

	SharedDataPipelineLayoutElementsInternal& SharedDataSimplifierCoreInternal::GetSharedDataPipelineLayoutElements()
	{
		return _pipelineLayoutData;
	}

	SharedDataRenderPassElementsInternal& SharedDataSimplifierCoreInternal::GetSharedDataRenderPassElements()
	{
		return _renderPassData;
	}

	const SharedDataPipelineElementsInternal& SharedDataSimplifierCoreInternal::GetConstSharedDataPipelineElements() const
	{
		return _pipelineData;
	}

	const SharedDataPipelineLayoutElementsInternal& SharedDataSimplifierCoreInternal::GetConstSharedDataPipelineLayoutElements() const
	{
		return _pipelineLayoutData;
	}

	const SharedDataRenderPassElementsInternal& SharedDataSimplifierCoreInternal::GetSharedDataRenderPassElements() const
	{
		return _renderPassData;
	}

}