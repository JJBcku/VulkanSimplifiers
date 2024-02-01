#include "../pch.h"
#include "SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{
	SharedDataSimplifierCoreInternal::SharedDataSimplifierCoreInternal(size_t reserve) : _pipelineData(reserve)
	{
	}

	SharedDataSimplifierCoreInternal::~SharedDataSimplifierCoreInternal()
	{
	}

	SharedDataPipelineElementsInternal& SharedDataSimplifierCoreInternal::GetSharedDataPipelineElements()
	{
		return _pipelineData;
	}
}