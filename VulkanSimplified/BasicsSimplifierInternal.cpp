#include "pch.h"
#include "BasicsSimplifierInternal.h"

#include "VulkanCoreSimplifierInternal.h"
#include "WindowSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "DeviceCoreSimplifierInternal.h"

#include "DevicesSwapchainSimplifierInternal.h"

#include "Include/DeviceListSimplifier.h"

namespace VulkanSimplified
{

	BasicsSimplifierInternal::BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_windows = std::make_unique<WindowSimplifierInternal>(windowSettings);
		_core = std::make_unique<VulkanCoreSimplifierInternal>(appSettings);
		auto instance = _core->GetInstance();

		_surface = std::make_unique<SurfaceSimplifierInternal>(_windows->GetWindow(), instance);
		_deviceList = std::make_unique<DeviceListSimplifierInternal>(_core->GetUsedApiVersion(), instance, _surface->GetSurface());
	}

	BasicsSimplifierInternal::~BasicsSimplifierInternal()
	{
		if (_swapchain)
		{
			_swapchain.reset();
		}

		_deviceList.reset();
		_surface->PreDestructionCall(_core->GetInstance());
		_surface.reset();
		_core.reset();
		_windows.reset();
		SDL_Quit();
	}

	DeviceListSimplifier BasicsSimplifierInternal::GetDeviceListSimplifier()
	{
		return DeviceListSimplifier(*_deviceList);
	}

	void BasicsSimplifierInternal::CreateSwapchain(ListObjectID<DeviceCoreSimplifierInternal> deviceID, SwapchainSettings settings, bool recreate)
	{
		if (!recreate && (_swapchain))
			throw std::runtime_error("BasicsSimplifierInternal::CreateSwapchain Error : Program tried to create already created swapchain!");

		auto& deviceCore = _deviceList->GetConstDeviceCore(deviceID);

		auto device = deviceCore.GetDevice();
		auto physicalDevice = deviceCore.GetPhysicalDevice();

		auto surface = _surface->GetSurface();

		_deviceList->UpdateSurfaceCapabilities(surface);
		auto deviceInfo = _deviceList->GetDeviceInfo(physicalDevice);

		if (_swapchain)
		{
			_swapchain->RecreateSwapchain(device, surface, deviceInfo, settings);
		}
		else
		{
			_swapchain = std::make_unique<DevicesSwapchainSimplifier>(device, surface, deviceInfo, settings);
		}
	}

}


