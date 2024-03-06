#include "../Other/pch.h"
#include "../Include/SharedData/SharedDataSimplifierCore.h"

#include "../Include/SharedData/SharedDataPipelineElements.h"
#include "../Include/SharedData/SharedDataPipelineLayoutElements.h"
#include "../Include/SharedData/SharedDataRenderPassElements.h"

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