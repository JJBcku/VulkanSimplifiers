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

	class DeviceScore
	{
		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> _scoringFunction;
		intmax_t _score;
		size_t _deviceID, _padding;

	public:
		DeviceScore(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t deviceID, intmax_t score);

		DeviceScore(const DeviceScore&) = default;
		DeviceScore(DeviceScore&& other);

		DeviceScore& operator=(const DeviceScore&) = default;
		DeviceScore& operator=(DeviceScore&& other);

		std::strong_ordering operator<=>(const DeviceScore&) const = default;
		bool operator==(const DeviceScore&) const = default;
	};

	class DeviceListSimplifierInternal
	{
		ListTemplate<std::function<intmax_t (const SimplifiedDeviceInfo&)>> _scoringFunctions;
		std::vector<DeviceScore> _deviceScoresList;

		std::vector<DeviceInfo> _deviceList;

		uint32_t _apiVersion, padding;

		DeviceFeatures QueryDeviceFeatures(VkPhysicalDevice device) const;
		DeviceProperties QueryDeviceProperties(VkPhysicalDevice device) const;
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;
		QueueFamilies QueryFamiliesSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;

		void EnumeratePhysicalDevices(VkInstance instance, VkSurfaceKHR surface);

		SimplifiedDeviceInfo SimplifyDeviceInfo(const DeviceInfo& deviceInfo) const;

	public:
		DeviceListSimplifierInternal(uint32_t apiVersion, VkInstance instance, VkSurfaceKHR surface);
		~DeviceListSimplifierInternal();

		DeviceListSimplifierInternal(const DeviceListSimplifierInternal&) = delete;
		DeviceListSimplifierInternal(DeviceListSimplifierInternal&&) = delete;

		DeviceListSimplifierInternal& operator=(const DeviceListSimplifierInternal&) = delete;
		DeviceListSimplifierInternal& operator=(DeviceListSimplifierInternal&&) = delete;

		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function);
	};
}
