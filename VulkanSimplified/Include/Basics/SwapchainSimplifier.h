#pragma once

namespace VulkanSimplified
{
	class SwapchainSimplifierInternal;
	class DeviceDataListSimplifierInternal;

	class AutoCleanupSemaphore;
	class AutoCleanupFence;

	template<class T>
	class ListObjectID;

	struct SwapchainSettings;

	class SwapchainSimplifier
	{
		SwapchainSimplifierInternal& _internal;

		void CreateSwapchainMain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings, bool redo);

	public:
		SwapchainSimplifier(SwapchainSimplifierInternal& ref);
		~SwapchainSimplifier();

		SwapchainSimplifier& operator=(const SwapchainSimplifier&) noexcept = delete;

		void CreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings);
		void ReCreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings);

		uint32_t GetSwapchainImagesAmount() const;

		uint32_t GetSwapchainWidth() const;
		uint32_t GetSwapchainHeight() const;

		std::pair<uint32_t, bool> AcquireNextImage(uint64_t timeLimitInNanosecons, std::optional<ListObjectID<AutoCleanupSemaphore>> semaphoreID,
			std::optional<ListObjectID<AutoCleanupFence>> fenceID);

		bool PresentImage(const std::vector<ListObjectID<AutoCleanupSemaphore>>& waitSemaphores, uint32_t frameID);
	};
}

