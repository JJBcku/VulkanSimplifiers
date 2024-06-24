#include "../Other/pch.h"
#include "BasicsSimplifierInternalStructs.h"

namespace VulkanSimplified
{
	SwapChainSupportDetails::SwapChainSupportDetails()
	{
		capabilities = {};
		memset(padding, 0, sizeof(padding));
	}

	DeviceProperties::DeviceProperties()
	{
		properties = {};
		properties11 = {};
		properties12 = {};
		properties13 = {};

		memory = {};
	}

	DeviceFeatures::DeviceFeatures()
	{
		features = {};
		memset(padding, 0, sizeof(padding));
		features11 = {};
		features12 = {};
		features13 = {};
	}

	DeviceInfo::DeviceInfo() : queueFamilies(), swapChainSupport(), features(), properties()
	{
		padding = 0;
		device = VK_NULL_HANDLE;
	}
}
