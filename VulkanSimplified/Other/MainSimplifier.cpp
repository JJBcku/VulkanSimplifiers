#include "../Other/pch.h"
#include "../Include/MainSimplifier.h"

#include "MainSimplifierInternal.h"
#include "../Include/BasicsSimplifier.h"

#include "../Include/SharedDataSimplifierCore.h"

namespace VulkanSimplified
{

	MainSimplifier::MainSimplifier(size_t sharedDataReserveAmount)
	{
		_internal = std::make_unique<MainSimplifierInternal>(sharedDataReserveAmount);
	}

	MainSimplifier::~MainSimplifier()
	{
	}

	ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> MainSimplifier::AddInstance(WindowCreationData windowSettings, AppData appSettings)
	{
		return _internal->AddInstance(windowSettings, appSettings);
	}

	BasicsSimplifier MainSimplifier::GetInstanceSimplifier(ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID)
	{
		return BasicsSimplifier(_internal->GetInstanceSimplifier(instanceID));
	}

	SharedDataSimplifierCore MainSimplifier::GetSharedDataCoreSimplifier()
	{
		return SharedDataSimplifierCore(_internal->GetSharedDataCoreSimplifier());
	}

}
