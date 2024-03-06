#include "../Other/pch.h"
#include "../Include/Basics/SwapchainSimplifier.h"

#include "../Include/Basics/SwapchainSimplifierStructs.h"
#include "../Include/Basics/SwapchainSimplifierEnums.h"

#include "SwapchainSimplifierInternal.h"

namespace VulkanSimplified
{

	void SwapchainSimplifier::CreateSwapchainMain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings, bool redo)
	{
		_internal.CreateSwapchain(deviceID, settings, redo);
	}

	SwapchainSimplifier::SwapchainSimplifier(SwapchainSimplifierInternal& ref) : _internal(ref)
	{
	}

	SwapchainSimplifier::~SwapchainSimplifier()
	{
	}

	void SwapchainSimplifier::CreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings)
	{
		CreateSwapchainMain(deviceID, settings, false);
	}

	void SwapchainSimplifier::ReCreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings)
	{
		CreateSwapchainMain(deviceID, settings, true);
	}

	uint32_t SwapchainSimplifier::GetSwapchainImagesAmount() const
	{
		return _internal.GetSwapchainImagesAmount();
	}

	uint32_t SwapchainSimplifier::GetSwapchainWidth() const
	{
		return _internal.GetSwapchainWidth();
	}

	uint32_t SwapchainSimplifier::GetSwapchainHeight() const
	{
		return _internal.GetSwapchainHeight();
	}

	std::pair<uint32_t, bool> SwapchainSimplifier::AcquireNextImage(uint64_t timeLimitInNanosecons, std::optional<ListObjectID<AutoCleanupSemaphore>> semaphoreID,
		std::optional<ListObjectID<AutoCleanupFence>> fenceID)
	{
		return _internal.AcquireNextImage(timeLimitInNanosecons, semaphoreID, fenceID);
	}

	bool SwapchainSimplifier::PresentImage(const std::vector<ListObjectID<AutoCleanupSemaphore>>& waitSemaphores, uint32_t frameID)
	{
		return _internal.PresentImage(waitSemaphores, frameID);
	}

}