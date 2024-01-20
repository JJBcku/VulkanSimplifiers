#include "pch.h"
#include "BasicsSimplifierInternal.h"

#include "VulkanCoreSimplifierInternal.h"
#include "WindowSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"

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

}


