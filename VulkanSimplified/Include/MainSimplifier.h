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
		MainSimplifier(size_t sharedDataReserveAmount, WindowCreationData windowSettings, AppData appSettings);
		~MainSimplifier();

		MainSimplifier(const MainSimplifier&) noexcept = delete;

		MainSimplifier& operator=(const MainSimplifier&) noexcept = delete;

		BasicsSimplifier GetInstanceSimplifier();

		SharedDataSimplifierCore GetSharedDataCoreSimplifier();
	};
}