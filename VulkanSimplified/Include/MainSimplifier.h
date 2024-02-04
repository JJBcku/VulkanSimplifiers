#include "BasicsSimplifierSharedStructs.h"

#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class BasicsSimplifier;
	class BasicsSimplifierInternal;

	class SharedDataSimplifierCore;

	class MainSimplifierInternal;

	class MainSimplifier
	{
		std::unique_ptr<MainSimplifierInternal> _internal;

	public:
		MainSimplifier(size_t sharedDataReserveAmount);
		~MainSimplifier();

		MainSimplifier(const MainSimplifier&) noexcept = delete;

		MainSimplifier& operator=(const MainSimplifier&) noexcept = delete;

		ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> AddInstance(WindowCreationData windowSettings, AppData appSettings);

		BasicsSimplifier GetInstanceSimplifier(ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID);

		SharedDataSimplifierCore GetSharedDataCoreSimplifier();
	};
}