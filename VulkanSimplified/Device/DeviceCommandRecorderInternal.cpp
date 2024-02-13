#include "../Other/pch.h"
#include "DeviceCommandRecorderInternal.h"

namespace VulkanSimplified
{

	DeviceCommandRecorderInternal::DeviceCommandRecorderInternal(VkCommandBuffer commandBuffer) : _commandBuffer(commandBuffer), _ppadding(nullptr)
	{
	}

	DeviceCommandRecorderInternal::~DeviceCommandRecorderInternal()
	{
	}

}