#include "../Other/pch.h"
#include "BasicsSimplifierInternal.h"

#include "VulkanCoreSimplifierInternal.h"
#include "WindowSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "../Device/DeviceCoreSimplifierInternal.h"

#include "SwapchainSimplifierInternal.h"

#include "../Include/Basics/DeviceListSimplifier.h"

namespace VulkanSimplified
{
	BasicsSimplifierInternal::BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings,
		const SharedDataSimplifierCoreInternal& sharedDataList) : _sharedDataList(sharedDataList), _windows(windowSettings), _core(appSettings), _surface(_windows, _core),
		_deviceList(_core, _surface, _swapchain, _sharedDataList), _swapchain(_windows, _surface, _deviceList)
	{
		_ppadding = nullptr;
	}

	BasicsSimplifierInternal::~BasicsSimplifierInternal()
	{
	}

	WindowSimplifierInternal& BasicsSimplifierInternal::GetWindowSimplifier()
	{
		return _windows;
	}

	DeviceListSimplifierInternal& BasicsSimplifierInternal::GetDeviceListSimplifier()
	{
		return _deviceList;
	}

	SwapchainSimplifierInternal& BasicsSimplifierInternal::GetSwapchainSimplifier()
	{
		return _swapchain;
	}

	const DeviceListSimplifierInternal& BasicsSimplifierInternal::GetDeviceListSimplifier() const
	{
		return _deviceList;
	}

	const SwapchainSimplifierInternal& BasicsSimplifierInternal::GetSwapchainSimplifier() const
	{
		return _swapchain;
	}

	const WindowSimplifierInternal& BasicsSimplifierInternal::GetWindowSimplifier() const
	{
		return _windows;
	}

}


