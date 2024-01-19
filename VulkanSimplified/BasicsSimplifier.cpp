#include "pch.h"
#include "Include/BasicsSimplifier.h"

#include "BasicsSimplifierInternal.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings)
	{
		_internal = std::make_unique<BasicsSimplifierInternal>(windowSettings, appSettings);
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
		_internal.reset();
	}

	DeviceListSimplifier BasicsSimplifier::GetDeviceListSimplifier()
	{
		return _internal->GetDeviceListSimplifier();
	}

}