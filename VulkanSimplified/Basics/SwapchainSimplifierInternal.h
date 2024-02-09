#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	struct SimplifiedDeviceInfo;
	struct DeviceInfo;

	struct SwapchainSettings;

	enum class SwapchainImageAmount : uint64_t;
	enum class SwapchainPresentMode : uint64_t;
	enum class SwapchainFormatType : uint64_t;

	class DeviceCoreSimplifierInternal;
	class SurfaceSimplifierInternal;
	class WindowSimplifierInternal;
	class DeviceListSimplifierInternal;
	class DeviceDataListSimplifierInternal;

	class SwapchainSimplifierInternal
	{
		const WindowSimplifierInternal& _window;
		const SurfaceSimplifierInternal& _surface;
		const DeviceListSimplifierInternal& _deviceList;
		void* _ppadding;

		VkSwapchainKHR _swapchain;
		VkDevice _device;
		VkPhysicalDevice _physicalDevice;
		VkFormat _format;
		char _padding[8 - sizeof(_format)];
		VkExtent2D _swapchainExtend;

		std::vector<VkImage> _swapchainImages;
		std::vector<VkImageView> _swapchainImageViews;

		char _padding2[16 - ((sizeof(_swapchainImageViews) + sizeof(_swapchainImages)) % 8)];

		VkFormat GetSwapchainFormat(SwapchainFormatType format) const;
		VkFormat GetSwapchainFormat8bit(const std::vector<VkSurfaceFormatKHR>& formats) const;
		VkFormat GetSwapchainFormat10bit(const std::vector<VkSurfaceFormatKHR>& formats) const;
		VkFormat GetSwapchainFormat12bit(const std::vector<VkSurfaceFormatKHR>& formats) const;
		VkFormat GetSwapchainFormat16bit(const std::vector<VkSurfaceFormatKHR>& formats) const;

		VkPresentModeKHR GetSwapchainPresentMode(SwapchainPresentMode presentMode, const SimplifiedDeviceInfo& info) const;
		uint32_t GetSwapchainImageAmount(SwapchainImageAmount imageAmount, uint32_t minAmount, uint32_t maxAmount) const;

		VkExtent2D GetImageExtend(const DeviceInfo& info) const;

		void GetSwapchainImages();
		void CreateSwapchainImageViews();

		void DestroySwapchain();

	public:
		SwapchainSimplifierInternal(const WindowSimplifierInternal& window, const SurfaceSimplifierInternal& surface, const DeviceListSimplifierInternal& deviceList);
		~SwapchainSimplifierInternal();

		SwapchainSimplifierInternal& operator=(const SwapchainSimplifierInternal&) noexcept = delete;

		void CreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings, bool recreate);

		bool DoSwapchainExist() const;

		uint32_t GetSwapchainWidth() const;
		uint32_t GetSwapchainHeight() const;

		VkFormat GetSwapchainFormat() const;
	};
}
