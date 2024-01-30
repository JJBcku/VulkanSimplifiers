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

	ListObjectID<VkVertexInputBindingDescription> SharedDataSimplifierCore::AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex)
	{
		return _internal->AddBindingDescription(binding, stride, useInstanceIndex);
	}

}