#include "../Other/pch.h"
#include "../Include/Basics/SwapchainSimplifierStructs.h"

#include "../Include/Basics/SwapchainSimplifierEnums.h"

namespace VulkanSimplified
{
	SwapchainSettings::SwapchainSettings()
	{
		memset(this, 0, sizeof(SwapchainSettings));
	}
}