#pragma once

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SwapchainSimplifier;
	class WindowSimplifier;
	class DeviceListSimplifier;

	struct WindowCreationData;
	struct AppData;
	struct SwapchainSettings;

	class BasicsSimplifier
	{
		BasicsSimplifierInternal& _internal;
		void* _ppadding;

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

