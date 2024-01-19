#pragma once

#include "Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	struct QueueFamilies
	{
		uint64_t graphicsFamily, computeFamily, transferFamily;

		QueueFamilies();
	};

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
		SwapChainSupportDetails swapChainSupport;
		QueueFamilies queueFamilies;
		DeviceFeatures features;
		DeviceProperties properties;

		DeviceInfo();
	};

	struct SimplifiedDeviceInfo;

	class DeviceListSimplifier
	{
		ListTemplate<std::function<intmax_t (const SimplifiedDeviceInfo&)>> _scoringFunctions;
		std::vector<std::pair<IDType, intmax_t>> _deviceScoresList;

		std::vector<DeviceInfo> _deviceList;

		uint32_t _apiVersion, padding;

		DeviceFeatures QueryDeviceFeatures(VkPhysicalDevice device) const;
		DeviceProperties QueryDeviceProperties(VkPhysicalDevice device) const;
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;
		QueueFamilies QueryFamiliesSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;

		void EnumeratePhysicalDevices(VkInstance instance, VkSurfaceKHR surface);

		SimplifiedDeviceInfo SimplifyDeviceInfo(const DeviceInfo& deviceInfo) const;

	public:
		DeviceListSimplifier(uint32_t apiVersion, VkInstance instance, VkSurfaceKHR surface);
		~DeviceListSimplifier();

		DeviceListSimplifier(const DeviceListSimplifier&) = delete;
		DeviceListSimplifier(DeviceListSimplifier&&) = delete;

		DeviceListSimplifier& operator=(const DeviceListSimplifier&) = delete;
		DeviceListSimplifier& operator=(DeviceListSimplifier&&) = delete;
	};
}
