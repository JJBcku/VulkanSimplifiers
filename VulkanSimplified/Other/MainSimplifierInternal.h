#pragma once

#include "../Basics/BasicsSimplifierInternal.h"
#include "../SharedData/SharedDataSimplifierCoreInternal.h"

#include "../Include/VulkanSimplifierListTemplate.h"

#include "../Include/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class MainSimplifierInternal
	{
		SharedDataSimplifierCoreInternal _sharedData;
		ListTemplate<std::unique_ptr<BasicsSimplifierInternal>> _vulkanInstances;

	public:
		MainSimplifierInternal(size_t sharedDataReserveAmount);
		~MainSimplifierInternal();

		MainSimplifierInternal(const MainSimplifierInternal&) noexcept = delete;

		MainSimplifierInternal& operator=(const MainSimplifierInternal&) = delete;

		ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> AddInstance(WindowCreationData windowSettings, AppData appSettings);

		BasicsSimplifierInternal& GetInstanceSimplifier(ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID);
		SharedDataSimplifierCoreInternal& GetSharedDataCoreSimplifier();
	};
}

