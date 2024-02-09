#include "../Other/pch.h"
#include "MainSimplifierInternal.h"

namespace VulkanSimplified
{

	MainSimplifierInternal::MainSimplifierInternal(size_t sharedDataReserveAmount) : _sharedData(sharedDataReserveAmount, *this)
	{
	}

	MainSimplifierInternal::~MainSimplifierInternal()
	{
	}

	ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> MainSimplifierInternal::AddInstance(WindowCreationData windowSettings, AppData appSettings)
	{
		std::unique_ptr<BasicsSimplifierInternal> add = std::make_unique<BasicsSimplifierInternal>(windowSettings, appSettings, _sharedData);

		return _vulkanInstances.AddObject(std::move(add));
	}

	BasicsSimplifierInternal& MainSimplifierInternal::GetInstanceSimplifier(ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID)
	{
		return *_vulkanInstances.GetObject(instanceID);
	}

	SharedDataSimplifierCoreInternal& MainSimplifierInternal::GetSharedDataCoreSimplifier()
	{
		return _sharedData;
	}

	const BasicsSimplifierInternal& MainSimplifierInternal::GetInstanceSimplifier(ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID) const
	{
		return *_vulkanInstances.GetConstObject(instanceID);
	}

	const SharedDataSimplifierCoreInternal& MainSimplifierInternal::GetSharedDataCoreSimplifier() const
	{
		return _sharedData;
	}

}