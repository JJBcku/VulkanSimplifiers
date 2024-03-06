#include "../Other/pch.h"
#include "MainSimplifierInternal.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{

	MainSimplifierInternal::MainSimplifierInternal(size_t sharedDataReserveAmount, WindowCreationData windowSettings, AppData appSettings) : _sharedData(sharedDataReserveAmount, _vulkanInstance),
		_vulkanInstance(windowSettings, appSettings, _sharedData)
	{
	}

	MainSimplifierInternal::~MainSimplifierInternal()
	{
	}

	BasicsSimplifierInternal& MainSimplifierInternal::GetInstanceSimplifier()
	{
		return _vulkanInstance;
	}

	SharedDataSimplifierCoreInternal& MainSimplifierInternal::GetSharedDataCoreSimplifier()
	{
		return _sharedData;
	}

	const BasicsSimplifierInternal& MainSimplifierInternal::GetInstanceSimplifier() const
	{
		return _vulkanInstance;
	}

	const SharedDataSimplifierCoreInternal& MainSimplifierInternal::GetSharedDataCoreSimplifier() const
	{
		return _sharedData;
	}

}