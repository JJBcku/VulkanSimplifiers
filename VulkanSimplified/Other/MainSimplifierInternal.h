#pragma once

#include "../Basics/BasicsSimplifierInternal.h"
#include "../SharedData/SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{
	struct WindowCreationData;
	struct AppData;

	class MainSimplifierInternal
	{
		SharedDataSimplifierCoreInternal _sharedData;
		BasicsSimplifierInternal _vulkanInstance;

	public:
		MainSimplifierInternal(size_t sharedDataReserveAmount, WindowCreationData windowSettings, AppData appSettings);
		~MainSimplifierInternal();

		MainSimplifierInternal(const MainSimplifierInternal&) noexcept = delete;

		MainSimplifierInternal& operator=(const MainSimplifierInternal&) = delete;

		BasicsSimplifierInternal& GetInstanceSimplifier();
		SharedDataSimplifierCoreInternal& GetSharedDataCoreSimplifier();

		const BasicsSimplifierInternal& GetInstanceSimplifier() const;
		const SharedDataSimplifierCoreInternal& GetSharedDataCoreSimplifier() const;
	};
}

