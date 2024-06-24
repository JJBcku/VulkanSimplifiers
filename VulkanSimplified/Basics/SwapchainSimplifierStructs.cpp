#include "../Other/pch.h"
#include "../Include/Basics/SwapchainSimplifierSharedStructs.h"

#include "../Include/Basics/SwapchainSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	SwapchainSettings::SwapchainSettings()
	{
		memset(this, 0, sizeof(SwapchainSettings));
	}
}