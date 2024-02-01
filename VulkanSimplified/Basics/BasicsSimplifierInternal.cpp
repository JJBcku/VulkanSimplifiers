#include "../pch.h"
#include "BasicsSimplifierInternal.h"

#include "VulkanCoreSimplifierInternal.h"
#include "WindowSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "../Device/DeviceCoreSimplifierInternal.h"

#include "SwapchainSimplifierInternal.h"

#include "../Include/DeviceListSimplifier.h"

namespace VulkanSimplified
{
	BasicsSimplifierInternal::BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings) : _windows(windowSettings), _core(appSettings), _surface(_windows, _core), _deviceList(_core, _surface), _swapchain(_windows, _surface, _deviceList)
	{
	}

	BasicsSimplifierInternal::~BasicsSimplifierInternal()
	{
	}

	DeviceListSimplifierInternal& BasicsSimplifierInternal::GetDeviceListSimplifier()
	{
		return _deviceList;
	}

	SwapchainSimplifierInternal& BasicsSimplifierInternal::GetSwapchainSimplifier()
	{
		return _swapchain;
	}

}


