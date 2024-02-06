#include "../Other/pch.h"
#include "../Include/BasicsSimplifier.h"

#include "BasicsSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "../Include/SwapchainSimplifier.h"

#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(BasicsSimplifierInternal& ref) : _internal(ref)
	{
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
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