#include "../Other/pch.h"
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
		return SharedDataPipelineElements(_internal.GetSharedDataPipelineElements());
	}

	SharedDataPipelineLayoutElements SharedDataSimplifierCore::GetSharedDataPipelineLayoutElements()
	{
		return SharedDataPipelineLayoutElements(_internal.GetSharedDataPipelineLayoutElements());
	}

	SharedDataRenderPassElements SharedDataSimplifierCore::GetSharedDataRenderPassElements()
	{
		return SharedDataRenderPassElements(_internal.GetSharedDataRenderPassElements());
	}

}