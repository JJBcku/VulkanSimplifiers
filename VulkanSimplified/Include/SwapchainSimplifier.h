#pragma once

#include "VulkanSimplifierListTemplate.h"

#include "DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class SwapchainSimplifierInternal;
	class DeviceDataListSimplifierInternal;

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

		uint32_t GetSwapchainWidth() const;
		uint32_t GetSwapchainHeight() const;
	};
}

