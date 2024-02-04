#pragma once

#include "BasicsSimplifierSharedStructs.h"
#include "DeviceListSimplifier.h"

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SwapchainSimplifier;

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

		DeviceListSimplifier GetDeviceListSimplifier();

		SwapchainSimplifier GetSwapchainSimplifier();
	};
}

