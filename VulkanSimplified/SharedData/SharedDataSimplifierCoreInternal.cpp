#include "../Other/pch.h"
#include "SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{

	SharedDataSimplifierCoreInternal::SharedDataSimplifierCoreInternal(size_t reserve) : _pipelineData(reserve), _pipelineLayoutData(reserve)
	{
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

	const SharedDataPipelineElementsInternal& SharedDataSimplifierCoreInternal::GetConstSharedDataPipelineElements() const
	{
		return _pipelineData;
	}

	const SharedDataPipelineLayoutElementsInternal& SharedDataSimplifierCoreInternal::GetConstSharedDataPipelineLayoutElements() const
	{
		return _pipelineLayoutData;
	}

}