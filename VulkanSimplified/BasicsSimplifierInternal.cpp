#include "pch.h"
#include "BasicsSimplifierInternal.h"

#include "VulkanCoreSimplifier.h"
#include "WindowSimplifier.h"
#include "SurfaceSimplifier.h"
#include "DeviceListSimplifierInternal.h"

#include "Include/DeviceListSimplifier.h"

namespace VulkanSimplified
{

	BasicsSimplifierInternal::BasicsSimplifierInternal(WindowCreationData windowSettings, AppData appSettings)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_windows = std::make_unique<WindowSimplifier>(windowSettings);
		_core = std::make_unique<VulkanCoreSimplifier>(appSettings);
		auto instance = _core->GetInstance();

		_surface = std::make_unique<SurfaceSimplifier>(_windows->GetWindow(), instance);
		_deviceList = std::make_unique<DeviceListSimplifierInternal>(_core->GetUsedApiVersion(), instance, _surface->GetSurface());
	}

	BasicsSimplifierInternal::~BasicsSimplifierInternal()
	{
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


