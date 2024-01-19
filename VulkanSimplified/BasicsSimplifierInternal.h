#pragma once

namespace VulkanSimplified
{
	class VulkanCoreSimplifierInternal;
	class WindowSimplifierInternal;
	class SurfaceSimplifierInternal;
	class DeviceListSimplifier;
	class DeviceListSimplifierInternal;

	struct WindowCreationData;
	struct AppData;

	class BasicsSimplifierInternal
	{
		std::unique_ptr<VulkanCoreSimplifierInternal> _core;
		std::unique_ptr<WindowSimplifierInternal> _windows;
		std::unique_ptr<SurfaceSimplifierInternal> _surface;
		std::unique_ptr<DeviceListSimplifierInternal> _deviceList;

	public:
		BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifierInternal();

		BasicsSimplifierInternal(const BasicsSimplifierInternal&) = delete;
		BasicsSimplifierInternal& operator= (const BasicsSimplifierInternal&) = delete;

		DeviceListSimplifier GetDeviceListSimplifier();
	};
}


