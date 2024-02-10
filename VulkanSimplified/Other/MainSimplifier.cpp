#include "../Other/pch.h"
#include "../Include/MainSimplifier.h"

#include "MainSimplifierInternal.h"
#include "../Include/BasicsSimplifier.h"

#include "../Include/SharedDataSimplifierCore.h"

namespace VulkanSimplified
{

	MainSimplifier::MainSimplifier(size_t sharedDataReserveAmount, WindowCreationData windowSettings, AppData appSettings)
	{
		_internal = std::make_unique<MainSimplifierInternal>(sharedDataReserveAmount, windowSettings, appSettings);
	}

	MainSimplifier::~MainSimplifier()
	{
	}

	BasicsSimplifier MainSimplifier::GetInstanceSimplifier()
	{
		return BasicsSimplifier(_internal->GetInstanceSimplifier());
	}

	SharedDataSimplifierCore MainSimplifier::GetSharedDataCoreSimplifier()
	{
		return SharedDataSimplifierCore(_internal->GetSharedDataCoreSimplifier());
	}

}
