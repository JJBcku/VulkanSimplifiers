#pragma once

#include "../Other/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class SurfaceSimplifierInternal;
	class SwapchainSimplifierInternal;
	class VulkanCoreSimplifierInternal;
	class SharedDataSimplifierCoreInternal;

	class DeviceDataListSimplifierInternal;

	struct SimplifiedDeviceInfo;
	struct DeviceInfo;

	struct DeviceSettings;
	struct DeviceFeatures;
	struct DeviceProperties;
	struct SwapChainSupportDetails;
	struct QueueFamilies;

	class DeviceScore
	{
		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> _scoringFunction;
		intmax_t _score;
		size_t _deviceID, _padding;

	public:
		DeviceScore(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t deviceID, intmax_t score);

		DeviceScore(const DeviceScore&) = default;
		DeviceScore(DeviceScore&& other) noexcept;

		DeviceScore& operator=(const DeviceScore&) = default;
		DeviceScore& operator=(DeviceScore&& other) noexcept;

		std::strong_ordering operator<=>(const DeviceScore&) const = default;
		bool operator==(const DeviceScore&) const = default;

		std::strong_ordering operator<=>(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction) const;
		bool operator==(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction) const;

		size_t GetDeviceID() const;
	};

	class DeviceListSimplifierInternal
	{
		const VulkanCoreSimplifierInternal& _coreSimplifier;
		const SurfaceSimplifierInternal& _surfaceSimplifier;
		const SwapchainSimplifierInternal& _swapchain;
		const SharedDataSimplifierCoreInternal& _sharedDataList;

		ListTemplate<std::function<intmax_t (const SimplifiedDeviceInfo&)>> _scoringFunctions;
		std::vector<DeviceScore> _deviceScoresList;

		std::vector<std::pair<SimplifiedDeviceInfo, VkPhysicalDevice>> _deviceList;

		ListTemplate<std::unique_ptr<DeviceDataListSimplifierInternal>> _logicalDevices;

		uint32_t _apiVersion, padding;

	private:
		DeviceFeatures QueryDeviceFeatures(VkPhysicalDevice device) const;
		DeviceProperties QueryDeviceProperties(VkPhysicalDevice device) const;
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;
		QueueFamilies QueryFamiliesSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;

		void EnumeratePhysicalDevices();

		SimplifiedDeviceInfo SimplifyDeviceInfo(const DeviceInfo& deviceInfo) const;

	public:
		DeviceListSimplifierInternal(const VulkanCoreSimplifierInternal& coreSimplifier, const SurfaceSimplifierInternal& surfaceSimplifier,
			const SwapchainSimplifierInternal& swapchain, const SharedDataSimplifierCoreInternal& sharedDataList);
		~DeviceListSimplifierInternal();

		DeviceListSimplifierInternal(const DeviceListSimplifierInternal&) = delete;
		DeviceListSimplifierInternal(DeviceListSimplifierInternal&&) = delete;

		DeviceListSimplifierInternal& operator=(const DeviceListSimplifierInternal&) = delete;
		DeviceListSimplifierInternal& operator=(DeviceListSimplifierInternal&&) = delete;

		SimplifiedDeviceInfo GetSimplifiedDeviceInfo(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID, size_t position);

		size_t GetQualifyingDevicesAmount(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID);

		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore);
		ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> CreateDevice(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t position, DeviceSettings settings);

		//std::pair<DeviceInfo, SimplifiedDeviceInfo> GetDeviceInfo(VkPhysicalDevice device);
		const DeviceDataListSimplifierInternal& GetConstDeviceDataListSimplifier(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID) const;
		DeviceDataListSimplifierInternal& GetDeviceDataListSimplifier(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID);

		//void UpdateSurfaceCapabilities(VkSurfaceKHR surface);

		DeviceDataListSimplifierInternal& GetDeviceDataList(const ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>>& deviceID);
	};
}
