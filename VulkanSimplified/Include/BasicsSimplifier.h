#pragma once

#include "BasicsSimplifierSharedStructs.h"
#include "DeviceListSimplifier.h"
#include "WindowSimplifier.h"

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SwapchainSimplifier;
	class WindowSimplifier;

	struct WindowCreationData;
	struct AppData;
	struct SwapchainSettings;

	class BasicsSimplifier
	{
		BasicsSimplifierInternal& _internal;

	public:
		BasicsSimplifier(BasicsSimplifierInternal& ref);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;

		WindowSimplifier GetWindowSimplifier();
		DeviceListSimplifier GetDeviceListSimplifier();
		SwapchainSimplifier GetSwapchainSimplifier();
	};
}

