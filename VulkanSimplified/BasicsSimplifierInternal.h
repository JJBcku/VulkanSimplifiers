#pragma once

#include "Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class VulkanCoreSimplifierInternal;
	class WindowSimplifierInternal;
	class SurfaceSimplifierInternal;
	class DeviceListSimplifier;
	class DeviceListSimplifierInternal;
	class DevicesSwapchainSimplifier;
	class DeviceCoreSimplifierInternal;

	struct WindowCreationData;
	struct AppData;

	struct SwapchainSettings;

	class BasicsSimplifierInternal
	{
		std::unique_ptr<VulkanCoreSimplifierInternal> _core;
		std::unique_ptr<WindowSimplifierInternal> _windows;
		std::unique_ptr<SurfaceSimplifierInternal> _surface;
		std::unique_ptr<DeviceListSimplifierInternal> _deviceList;

		std::unique_ptr<DevicesSwapchainSimplifier> _swapchain;

	public:
		BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifierInternal();

		BasicsSimplifierInternal(const BasicsSimplifierInternal&) = delete;
		BasicsSimplifierInternal& operator= (const BasicsSimplifierInternal&) = delete;

		DeviceListSimplifier GetDeviceListSimplifier();

		void CreateSwapchain(ListObjectID<DeviceCoreSimplifierInternal> deviceID, SwapchainSettings settings, bool recreate);
	};
}


