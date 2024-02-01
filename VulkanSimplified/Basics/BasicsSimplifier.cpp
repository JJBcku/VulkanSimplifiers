#include "../pch.h"
#include "../Include/BasicsSimplifier.h"

#include "BasicsSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "../Include/SwapchainSimplifier.h"

#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings)
	{
		_internal = std::make_unique<BasicsSimplifierInternal>(windowSettings, appSettings);
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
		_internal.reset();
	}

	DeviceListSimplifier BasicsSimplifier::GetDeviceListSimplifier()
	{
		return DeviceListSimplifier(_internal->GetDeviceListSimplifier());
	}

	SwapchainSimplifier BasicsSimplifier::GetSwapchainSimplifier()
	{
		return SwapchainSimplifier(_internal->GetSwapchainSimplifier());
	}

}