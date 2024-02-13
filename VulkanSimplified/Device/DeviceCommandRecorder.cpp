#include "../Other/pch.h"
#include "../Include/DeviceCommandRecorder.h"

#include "DeviceCommandRecorderInternal.h"

namespace VulkanSimplified
{

	DeviceCommandRecorder::DeviceCommandRecorder(DeviceCommandRecorderInternal& ref) : _internal(ref)
	{
	}

	DeviceCommandRecorder::~DeviceCommandRecorder()
	{
	}

}