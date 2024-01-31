#pragma once

#include "Include/VulkanSimplifierListTemplate.h"

#include "WindowSimplifierInternal.h"
#include "VulkanCoreSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"

#include "SwapchainSimplifierInternal.h"

namespace VulkanSimplified
{
	class DeviceListSimplifier;

	class DeviceCoreSimplifierInternal;

	struct WindowCreationData;
	struct AppData;

	struct SwapchainSettings;

	class BasicsSimplifierInternal
	{
		WindowSimplifierInternal _windows;
		VulkanCoreSimplifierInternal _core;
		SurfaceSimplifierInternal _surface;
		DeviceListSimplifierInternal _deviceList;

		SwapchainSimplifierInternal _swapchain;

	public:
		BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifierInternal();

		BasicsSimplifierInternal(const BasicsSimplifierInternal&) = delete;
		BasicsSimplifierInternal& operator= (const BasicsSimplifierInternal&) = delete;

		DeviceListSimplifierInternal& GetDeviceListSimplifier();

		SwapchainSimplifierInternal& GetSwapchainSimplifier();
	};
}


