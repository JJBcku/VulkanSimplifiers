#include "pch.h"
#include "Include/BasicsSimplifier.h"

#include "BasicsSimplifierInternal.h"

#include "Include/DeviceSimplifierSharedStructs.h"

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
		return _internal->GetDeviceListSimplifier();
	}

	void BasicsSimplifier::CreateSwapchain(ListObjectID<DeviceCoreSimplifierInternal> deviceID, SwapchainSettings settings, bool recreate)
	{
		_internal->CreateSwapchain(deviceID, settings, recreate);
	}

}