#include "../Other/pch.h"
#include "../Include/Basics/BasicsSimplifier.h"

#include "BasicsSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "../Include/Basics/SwapchainSimplifier.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"
#include "../Include/Basics/DeviceListSimplifier.h"
#include "../Include/Basics/WindowSimplifier.h"

#include "../Include/Device/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(BasicsSimplifierInternal& ref) : _internal(ref), _ppadding(nullptr)
	{
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
	}

	WindowSimplifier BasicsSimplifier::GetWindowSimplifier()
	{
		return WindowSimplifier(_internal.GetWindowSimplifier());
	}

	DeviceListSimplifier BasicsSimplifier::GetDeviceListSimplifier()
	{
		return DeviceListSimplifier(_internal.GetDeviceListSimplifier());
	}

	SwapchainSimplifier BasicsSimplifier::GetSwapchainSimplifier()
	{
		return SwapchainSimplifier(_internal.GetSwapchainSimplifier());
	}

}