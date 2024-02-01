#include "../pch.h"
#include "../Include/SwapchainSimplifier.h"

#include "SwapchainSimplifierInternal.h"

namespace VulkanSimplified
{

	void SwapchainSimplifier::CreateSwapchainMain(ListObjectID<DeviceDataListSimplifierInternal> deviceID, SwapchainSettings settings, bool redo)
	{
		_internal.CreateSwapchain(deviceID, settings, redo);
	}

	SwapchainSimplifier::SwapchainSimplifier(SwapchainSimplifierInternal& ref) : _internal(ref)
	{
	}

	SwapchainSimplifier::~SwapchainSimplifier()
	{
	}

	void SwapchainSimplifier::CreateSwapchain(ListObjectID<DeviceDataListSimplifierInternal> deviceID, SwapchainSettings settings)
	{
		CreateSwapchainMain(deviceID, settings, false);
	}

	void SwapchainSimplifier::ReCreateSwapchain(ListObjectID<DeviceDataListSimplifierInternal> deviceID, SwapchainSettings settings)
	{
		CreateSwapchainMain(deviceID, settings, true);
	}

	uint32_t SwapchainSimplifier::GetSwapchainWidth() const
	{
		return _internal.GetSwapchainWidth();
	}

	uint32_t SwapchainSimplifier::GetSwapchainHeight() const
	{
		return _internal.GetSwapchainHeight();
	}

}