#include "pch.h"
#include "Include/SharedDataSimplifierCore.h"

#include "SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{

	SharedDataSimplifierCore::SharedDataSimplifierCore(size_t reserveListElements)
	{
		_internal = std::make_unique<SharedDataSimplifierCoreInternal>(reserveListElements);
	}

	SharedDataSimplifierCore::~SharedDataSimplifierCore()
	{
	}

	SharedDataPipelineElements SharedDataSimplifierCore::GetSharedDataPipelineElements()
	{
		return _internal->GetSharedDataPipelineElements();
	}

}