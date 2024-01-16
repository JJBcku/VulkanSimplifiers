#pragma once

namespace VulkanSimplified
{
	class VulkanCoreSimplifier;
	class WindowSimplifier;
	class SurfaceSimplifier;
	class DeviceListSimplifier;

	struct WindowCreationData;
	struct AppData;

	class BasicsSimplifierInternal
	{
		std::unique_ptr<VulkanCoreSimplifier> _core;
		std::unique_ptr<WindowSimplifier> _windows;
		std::unique_ptr<SurfaceSimplifier> _surface;
		std::unique_ptr<DeviceListSimplifier> _deviceList;

	public:
		BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifierInternal();

		BasicsSimplifierInternal(const BasicsSimplifierInternal&) = delete;
		BasicsSimplifierInternal& operator= (const BasicsSimplifierInternal&) = delete;
	};
}


