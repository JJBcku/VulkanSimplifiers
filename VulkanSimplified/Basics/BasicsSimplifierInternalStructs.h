#pragma once

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		char padding[4];
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		SwapChainSupportDetails();
	};

	struct DeviceProperties
	{
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceVulkan11Properties properties11;
		VkPhysicalDeviceVulkan12Properties properties12;
		VkPhysicalDeviceVulkan13Properties properties13;
		VkPhysicalDeviceMemoryProperties memory;

		std::vector<VkExtensionProperties> availableExtensions;
		std::vector<void*> extra;

		DeviceProperties();
	};

	struct DeviceFeatures
	{
		VkPhysicalDeviceFeatures features;
		char padding[4];
		VkPhysicalDeviceVulkan11Features features11;
		VkPhysicalDeviceVulkan12Features features12;
		VkPhysicalDeviceVulkan13Features features13;

		DeviceFeatures();
	};

	struct DeviceInfo
	{
		VkPhysicalDevice device;
		size_t padding;
		QueueFamilies queueFamilies;
		SwapChainSupportDetails swapChainSupport;
		DeviceFeatures features;
		DeviceProperties properties;

		DeviceInfo();
	};
}
