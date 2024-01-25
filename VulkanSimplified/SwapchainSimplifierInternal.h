#pragma once

namespace VulkanSimplified
{
	struct SimplifiedDeviceInfo;
	struct DeviceInfo;

	struct SwapchainSettings;

	enum class SwapchainImageAmount : uint64_t;
	enum class SwapchainPresentMode : uint64_t;
	enum class SwapchainFormatType : uint64_t;

	class SwapchainSimplifier
	{
		VkSwapchainKHR _swapchain;
		VkDevice _swapchainDevice;
		VkFormat _swapchainFormat;
		char _padding[16 - (sizeof(_swapchainFormat) + sizeof(_swapchainDevice))];
		VkExtent2D _swapchainExtend;

		std::vector<VkImage> _swapchainImages;
		std::vector<VkImageView> _swapchainImageViews;

		//char _padding2[8 - (sizeof(_swapchainImages) % 8)];

		VkFormat GetSwapchainFormat(SwapchainFormatType format, const DeviceInfo& info) const;
		VkFormat GetSwapchainFormat8bit(const DeviceInfo& info) const;
		VkFormat GetSwapchainFormat10bit(const DeviceInfo& info) const;
		VkFormat GetSwapchainFormat12bit(const DeviceInfo& info) const;
		VkFormat GetSwapchainFormat16bit(const DeviceInfo& info) const;

		VkPresentModeKHR GetSwapchainPresentMode(SwapchainPresentMode presentMode, const SimplifiedDeviceInfo& info) const;
		uint32_t GetSwapchainImageAmount(SwapchainImageAmount imageAmount, uint32_t minAmount, uint32_t maxAmount) const;

		VkExtent2D GetImageExtend(const DeviceInfo& info) const;
		VkSurfaceTransformFlagBitsKHR GetImageTransform(const DeviceInfo& info) const;

		void DestroySwapchain();

		void GetSwapchainImages();
		void CreateSwapchainImageViews();

		void CreateSwapchain(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings);

	public:
		SwapchainSimplifier(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings);
		~SwapchainSimplifier();

		void RecreateSwapchain(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings);
	};
}
