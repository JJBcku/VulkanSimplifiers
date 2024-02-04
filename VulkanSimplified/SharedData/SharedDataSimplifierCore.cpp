#include "../pch.h"
#include "../Include/SharedDataSimplifierCore.h"

#include "SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{

	SharedDataSimplifierCore::SharedDataSimplifierCore(SharedDataSimplifierCoreInternal& ref) : _internal(ref)
	{
	}

	SharedDataSimplifierCore::~SharedDataSimplifierCore()
	{
	}

	SharedDataPipelineElements SharedDataSimplifierCore::GetSharedDataPipelineElements()
	{
		return _internal.GetSharedDataPipelineElements();
	}

}