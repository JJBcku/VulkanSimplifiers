#include "pch.h"
#include "SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{
	SharedDataSimplifierCoreInternal::SharedDataSimplifierCoreInternal(size_t reserve) : _pipelineData(reserve)
	{
	}

	SharedDataSimplifierCoreInternal::~SharedDataSimplifierCoreInternal()
	{
	}

	ListObjectID<VkVertexInputBindingDescription> SharedDataSimplifierCoreInternal::AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex)
	{
		return _pipelineData.AddBindingDescription(binding, stride, useInstanceIndex);
	}
}