#pragma once

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
		const SharedDataSimplifierCoreInternal& _sharedDataList;
		void* _ppadding;

		WindowSimplifierInternal _windows;
		VulkanCoreSimplifierInternal _core;
		SurfaceSimplifierInternal _surface;
		DeviceListSimplifierInternal _deviceList;

		SwapchainSimplifierInternal _swapchain;

	public:
		BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings, const SharedDataSimplifierCoreInternal& sharedDataList);
		~BasicsSimplifierInternal();

		BasicsSimplifierInternal(const BasicsSimplifierInternal&) = delete;
		BasicsSimplifierInternal& operator= (const BasicsSimplifierInternal&) = delete;

		WindowSimplifierInternal& GetWindowSimplifier();
		DeviceListSimplifierInternal& GetDeviceListSimplifier();
		SwapchainSimplifierInternal& GetSwapchainSimplifier();

		const DeviceListSimplifierInternal& GetDeviceListSimplifier() const;
		const SwapchainSimplifierInternal& GetSwapchainSimplifier() const;
		const WindowSimplifierInternal& GetWindowSimplifier() const;
	};
}


