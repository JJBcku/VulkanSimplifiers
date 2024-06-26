#include "../Other/pch.h"
#include "SwapchainSimplifierInternal.h"

#include "WindowSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "BasicsSimplifierInternalStructs.h"

#include "../Include/Basics/SwapchainSimplifierSharedEnums.h"
#include "../Include/Basics/SwapchainSimplifierSharedStructs.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"

#include "../Device/DeviceDataListSimplifierInternal.h"
#include "../Device/DeviceSynchronizationSimplifierInternal.h"
#include "../Device/DeviceImageSimplifierInternal.h"

namespace VulkanSimplified
{
	constexpr VkColorSpaceKHR colorspace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat(SwapchainFormatType format) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		uint32_t formatAmount = 0;
		std::vector<VkSurfaceFormatKHR> formats;

		auto surface = _surface.GetSurface();

		vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, surface, &formatAmount, nullptr);
		formats.resize(formatAmount);

		vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, surface, &formatAmount, formats.data());

		switch (format)
		{
		case VulkanSimplified::SwapchainFormatType::EIGHT_BIT:
			ret = GetSwapchainFormat8bit(formats);
			break;
		case VulkanSimplified::SwapchainFormatType::TEN_BIT:
			ret = GetSwapchainFormat10bit(formats);
			break;
		case VulkanSimplified::SwapchainFormatType::TWELVE_BIT:
			ret = GetSwapchainFormat12bit(formats);
			break;
		case VulkanSimplified::SwapchainFormatType::SIXTEEN_BIT:
			ret = GetSwapchainFormat16bit(formats);
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat8bit(const std::vector<VkSurfaceFormatKHR>& formats) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		for (auto& format : formats)
		{
			if (format.colorSpace == colorspace)
			{
				if (format.format == VK_FORMAT_R8G8B8A8_UNORM)
				{
					ret = format.format;
					break;
				}
				else if (format.format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					ret = format.format;
				}
				else if (format.format == VK_FORMAT_A8B8G8R8_UNORM_PACK32 && ret != VK_FORMAT_B8G8R8A8_UNORM)
				{
					ret = format.format;
				}
			}
		}

		return ret;
	}

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat10bit(const std::vector<VkSurfaceFormatKHR>& formats) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		for (auto& format : formats)
		{
			if (format.colorSpace == colorspace)
			{
				if (format.format == VK_FORMAT_A2R10G10B10_UNORM_PACK32)
				{
					ret = format.format;
					break;
				}
				else if (format.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
				{
					ret = format.format;
				}
			}
		}

		return ret;
	}

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat12bit(const std::vector<VkSurfaceFormatKHR>& formats) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		for (auto& format : formats)
		{
			if (format.colorSpace == colorspace)
			{
				if (format.format == VK_FORMAT_B10G11R11_UFLOAT_PACK32)
				{
					ret = format.format;
					break;
				}
			}
		}

		return ret;
	}

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat16bit(const std::vector<VkSurfaceFormatKHR>& formats) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		for (auto& format : formats)
		{
			if (format.colorSpace == colorspace)
			{
				if (format.format == VK_FORMAT_R16G16B16A16_UNORM)
				{
					ret = format.format;
					break;
				}
			}
		}

		return ret;
	}

	VkPresentModeKHR SwapchainSimplifierInternal::GetSwapchainPresentMode(SwapchainPresentMode presentMode, const SimplifiedDeviceInfo& info) const
	{
		VkPresentModeKHR ret = VK_PRESENT_MODE_MAX_ENUM_KHR;

		switch (presentMode)
		{
		case VulkanSimplified::SwapchainPresentMode::IMMEDIATE:
			ret = VK_PRESENT_MODE_IMMEDIATE_KHR;
			break;
		case VulkanSimplified::SwapchainPresentMode::MAILBOX:
			if (!info.mailboxPresentMode)
				throw std::runtime_error("DevicesSwapchainSimplifierInternal::GetSwapchainPresentMode: Program tried to enable mailbox present mode while it was unavailable!");
			ret = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		case VulkanSimplified::SwapchainPresentMode::FIFO:
			if (!info.fifoPresentMode)
				throw std::runtime_error("DevicesSwapchainSimplifierInternal::GetSwapchainPresentMode: Program tried to enable fifo present mode while it was unavailable!");
			ret = VK_PRESENT_MODE_FIFO_KHR;
			break;
		default:
			break;
		}

		return ret;
	}

	uint32_t SwapchainSimplifierInternal::GetSwapchainImageAmount(SwapchainImageAmount imageAmount, uint32_t minAmount, uint32_t maxAmount) const
	{
		uint32_t ret = 0;

		switch (imageAmount)
		{
		case SwapchainImageAmount::MIN:
			ret = minAmount;
			break;
		case SwapchainImageAmount::HALF_DIFFERENCE:
			ret = maxAmount - minAmount;
			ret = ret >> 1;
			ret += minAmount;
			break;
		case SwapchainImageAmount::MAX:
			ret = maxAmount;
			break;
		case SwapchainImageAmount::MIN_PLUS_ONE:
			ret = std::min(minAmount + 1, maxAmount);
			break;
		case SwapchainImageAmount::MAX_MINUS_ONE:
			ret = std::max(maxAmount - 1, minAmount);
			break;
		case SwapchainImageAmount::HALF_AMOUNT:
			ret = std::max(maxAmount >> 1, minAmount);
			break;
		default:
			break;
		}

		return ret;
	}

	VkExtent2D SwapchainSimplifierInternal::GetImageExtend(const DeviceInfo& info) const
	{
		return info.swapChainSupport.capabilities.currentExtent;
	}

	void SwapchainSimplifierInternal::DestroySwapchain()
	{
		if (_swapchain != VK_NULL_HANDLE)
		{
			auto& framebufferList = _deviceList.GetDeviceDataListSimplifier(_deviceID).GetDeviceImageSimplifier();

			framebufferList.DestroySwapchainFramebuffers();

			for (size_t i = 0; i < _swapchainImageViews.size(); ++i)
			{
				vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
			}
			_swapchainImageViews.clear();
			_swapchainImages.clear();

			vkDestroySwapchainKHR(_device, _swapchain, nullptr);
			_swapchain = VK_NULL_HANDLE;
		}

		_device = VK_NULL_HANDLE;
		_swapchainExtend = { 0, 0 };
	}

	bool SwapchainSimplifierInternal::DoSwapchainExist() const
	{
		return _swapchain != VK_NULL_HANDLE;
	}

	uint32_t SwapchainSimplifierInternal::GetSwapchainImagesAmount() const
	{
		return static_cast<uint32_t>(_swapchainImages.size());
	}

	uint32_t SwapchainSimplifierInternal::GetSwapchainWidth() const
	{
		return _swapchainExtend.width;
	}

	uint32_t SwapchainSimplifierInternal::GetSwapchainHeight() const
	{
		return _swapchainExtend.height;
	}

	VkFormat SwapchainSimplifierInternal::GetSwapchainFormat() const
	{
		return _format;
	}

	std::vector<VkImageView> SwapchainSimplifierInternal::GetSwapchainImageViewList() const
	{
		return _swapchainImageViews;
	}

	std::pair<uint32_t, bool> SwapchainSimplifierInternal::AcquireNextImage(uint64_t timeLimitInNanosecons, std::optional<ListObjectID<AutoCleanupSemaphore>> semaphoreID, std::optional<ListObjectID<AutoCleanupFence>> fenceID)
	{
		auto& device = _deviceList.GetConstDeviceDataListSimplifier(_deviceID);
		auto& synchronization = device.GetDeviceSynchronizationSimplifier();

		std::pair<uint32_t, bool> ret = { std::numeric_limits<uint32_t>::max(), false };

		VkSemaphore semaphore = VK_NULL_HANDLE;
		VkFence fence = VK_NULL_HANDLE;

		if (semaphoreID.has_value())
			semaphore = synchronization.GetSemaphore(semaphoreID.value());

		if (fenceID.has_value())
			fence = synchronization.GetFence(fenceID.value());

		VkResult result = vkAcquireNextImageKHR(_device, _swapchain, timeLimitInNanosecons, semaphore, fence, &ret.first);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("SwapchainSimplifierInternal::AcquireNextImage Error: Program failed to acquire next image!");

		if (result == VK_SUCCESS)
			ret.second = true;

		return ret;
	}

	bool SwapchainSimplifierInternal::PresentImage(const std::vector<ListObjectID<AutoCleanupSemaphore>>& waitSemaphores, uint32_t frameID)
	{
		if (waitSemaphores.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("SwapchainSimplifierInternal::PresentImage Error: signal semaphores overflow!");

		auto& device = _deviceList.GetConstDeviceDataListSimplifier(_deviceID);
		auto& synchro = device.GetDeviceSynchronizationSimplifier();
		auto& deviceCore = device.GetDeviceCoreSimplifier();
		
		VkQueue queue = deviceCore.GetQueue(VulkanSimplified::QueueFamilyType::GRAPHICS);

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &_swapchain;
		presentInfo.pImageIndices = &frameID;

		std::vector<VkSemaphore> semaphoreList;
		
		if (!waitSemaphores.empty())
		{
			semaphoreList = synchro.GetSemaphoresList(waitSemaphores);

			presentInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
			presentInfo.pWaitSemaphores = semaphoreList.data();
		}

		VkResult res = vkQueuePresentKHR(queue, &presentInfo);

		if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR && res != VK_ERROR_OUT_OF_DATE_KHR)
			throw std::runtime_error("SwapchainSimplifierInternal::PresentImage Error: Program failed to present an image!");

		return res == VK_SUCCESS;
	}

	void SwapchainSimplifierInternal::GetSwapchainImages()
	{
		uint32_t imagesAmount = 0;

		vkGetSwapchainImagesKHR(_device, _swapchain, &imagesAmount, nullptr);

		_swapchainImages.resize(imagesAmount);

		vkGetSwapchainImagesKHR(_device, _swapchain, &imagesAmount, _swapchainImages.data());

		CreateSwapchainImageViews();
	}

	void SwapchainSimplifierInternal::CreateSwapchainImageViews()
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = _format;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.layerCount = 1;
		createInfo.subresourceRange.levelCount = 1;

		_swapchainImageViews.resize(_swapchainImages.size());

		for (size_t i = 0; i < _swapchainImages.size(); ++i)
		{
			createInfo.image = _swapchainImages[i];

			if (vkCreateImageView(_device, &createInfo, nullptr, &_swapchainImageViews[i]) != VK_SUCCESS)
				throw std::runtime_error("DevicesSwapchainSimplifierInternal::CreateSwapchainImageViews Error: Program failed to create a view for a swapchain image!");
		}
	}

	void SwapchainSimplifierInternal::CreateSwapchain(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID, SwapchainSettings settings, bool recreate)
	{
		if (_swapchain != VK_NULL_HANDLE)
		{
			if (recreate)
			{
				DestroySwapchain();
			}
			else
			{
				throw std::runtime_error("DevicesSwapchainSimplifierInternal::CreateSwapchain Error: Program tried to create already existing swapchain!");
			}
		}

		_deviceID = deviceID;
		auto& deviceList = _deviceList.GetConstDeviceDataListSimplifier(deviceID);
		auto& device = deviceList.GetDeviceCoreSimplifier();

		_device = device.GetDevice();
		_physicalDevice = device.GetPhysicalDevice();

		assert(_device != VK_NULL_HANDLE);
		assert(_physicalDevice != VK_NULL_HANDLE);

		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _surface.GetSurface(), &_surfaceCapabilities) != VK_SUCCESS)
			throw std::runtime_error("SwapchainSimplifierInternal::CreateSwapchain Error: Program failed to query physical device surface capabilities!");

		VkSwapchainCreateInfoKHR createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _surface.GetSurface();

		_format = GetSwapchainFormat(settings.format);
		createInfo.imageFormat = _format;
		createInfo.imageColorSpace = colorspace;
		createInfo.imageArrayLayers = 1;
		_swapchainExtend.width = _window.GetWindowWidth();
		_swapchainExtend.height = _window.GetWindowHeight();

		_swapchainExtend.width = std::clamp(_swapchainExtend.width, _surfaceCapabilities.minImageExtent.width, _surfaceCapabilities.maxImageExtent.width);
		_swapchainExtend.height = std::clamp(_swapchainExtend.height, _surfaceCapabilities.minImageExtent.height, _surfaceCapabilities.maxImageExtent.height);
		createInfo.imageExtent = _swapchainExtend;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		auto info = device.GetDeviceInfo();
		createInfo.minImageCount = GetSwapchainImageAmount(settings.imageAmount, info.minSwapchainImages, info.maxSwapchainImages);

		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;

		createInfo.presentMode = GetSwapchainPresentMode(settings.presentMode, info);
		createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("DevicesSwapchainSimplifierInternal::CreateSwapchain Error: Program failed to create a swapchain!");
		}

		GetSwapchainImages();
	}

	SwapchainSimplifierInternal::SwapchainSimplifierInternal(const WindowSimplifierInternal& window, const SurfaceSimplifierInternal& surface,
		DeviceListSimplifierInternal& deviceList) : _window(window), _surface(surface), _deviceList(deviceList)
	{
		_ppadding = nullptr;

		_swapchain = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
		_physicalDevice = VK_NULL_HANDLE;
		_format = VK_FORMAT_MAX_ENUM;
		_swapchainExtend = { 0, 0 };
		_surfaceCapabilities = {};
		_upadding = 0;

		memset(_padding, 0, sizeof(_padding));
		memset(_padding2, 0, sizeof(_padding2));
	}

	SwapchainSimplifierInternal::~SwapchainSimplifierInternal()
	{
		DestroySwapchain();
	}

}