#pragma once

#include "BasicsSimplifierSharedStructs.h"
#include "DeviceListSimplifier.h"

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;

	struct WindowCreationData;
	struct AppData;
	struct SwapchainSettings;

	class BasicsSimplifier
	{
		std::unique_ptr<BasicsSimplifierInternal> _internal;

	public:
		BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;

		DeviceListSimplifier GetDeviceListSimplifier();

		void CreateSwapchain(ListObjectID<DeviceCoreSimplifierInternal> deviceID, SwapchainSettings settings, bool recreate);
	};
}

