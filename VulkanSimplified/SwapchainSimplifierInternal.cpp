#include "pch.h"
#include "SwapchainSimplifierInternal.h"

#include "DeviceListSimplifierInternal.h"

#include "Include/BasicsSimplifierSharedStructs.h"
#include "Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	constexpr VkColorSpaceKHR colorspace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

	VkFormat SwapchainSimplifier::GetSwapchainFormat(SwapchainFormatType format, const DeviceInfo& info) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;

		switch (format)
		{
		case VulkanSimplified::SwapchainFormatType::EIGHT_BIT:
			ret = GetSwapchainFormat8bit(info);
			break;
		case VulkanSimplified::SwapchainFormatType::TEN_BIT:
			ret = GetSwapchainFormat10bit(info);
			break;
		case VulkanSimplified::SwapchainFormatType::TWELVE_BIT:
			ret = GetSwapchainFormat12bit(info);
			break;
		case VulkanSimplified::SwapchainFormatType::SIXTEEN_BIT:
			ret = GetSwapchainFormat16bit(info);
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat SwapchainSimplifier::GetSwapchainFormat8bit(const DeviceInfo& info) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;
		auto& formatList = info.swapChainSupport.formats;

		for (auto& format : formatList)
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
			}
		}

		return ret;
	}

	VkFormat SwapchainSimplifier::GetSwapchainFormat10bit(const DeviceInfo& info) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;
		auto& formatList = info.swapChainSupport.formats;

		for (auto& format : formatList)
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

	VkFormat SwapchainSimplifier::GetSwapchainFormat12bit(const DeviceInfo& info) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;
		auto& formatList = info.swapChainSupport.formats;

		for (auto& format : formatList)
		{
			if (format.colorSpace == colorspace)
			{
				if (format.format == VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16)
				{
					ret = format.format;
					break;
				}
			}
		}

		return ret;
	}

	VkFormat SwapchainSimplifier::GetSwapchainFormat16bit(const DeviceInfo& info) const
	{
		VkFormat ret = VK_FORMAT_MAX_ENUM;
		auto& formatList = info.swapChainSupport.formats;

		for (auto& format : formatList)
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

	VkPresentModeKHR SwapchainSimplifier::GetSwapchainPresentMode(SwapchainPresentMode presentMode, const SimplifiedDeviceInfo& info) const
	{
		VkPresentModeKHR ret = VK_PRESENT_MODE_MAX_ENUM_KHR;

		switch (presentMode)
		{
		case VulkanSimplified::SwapchainPresentMode::IMMEDIATE:
			ret = VK_PRESENT_MODE_IMMEDIATE_KHR;
			break;
		case VulkanSimplified::SwapchainPresentMode::MAILBOX:
			if (!info.mailboxPresentMode)
				throw std::runtime_error("DevicesSwapchainSimplifier::GetSwapchainPresentMode: Program tried to enable mailbox present mode while it was unavailable!");
			ret = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		case VulkanSimplified::SwapchainPresentMode::FIFO:
			if (!info.fifoPresentMode)
				throw std::runtime_error("DevicesSwapchainSimplifier::GetSwapchainPresentMode: Program tried to enable fifo present mode while it was unavailable!");
			ret = VK_PRESENT_MODE_FIFO_KHR;
			break;
		default:
			break;
		}

		return ret;
	}

	uint32_t SwapchainSimplifier::GetSwapchainImageAmount(SwapchainImageAmount imageAmount, uint32_t minAmount, uint32_t maxAmount) const
	{
		uint32_t ret = 0;

		switch (imageAmount)
		{
		case SwapchainImageAmount::MIN:
			ret = minAmount;
			break;
		case SwapchainImageAmount::HALF:
			ret = maxAmount - minAmount;
			ret = ret >> 1;
			ret += minAmount;
			break;
		case SwapchainImageAmount::MAX:
			ret = maxAmount;
			break;
		default:
			break;
		}

		return ret;
	}

	VkExtent2D SwapchainSimplifier::GetImageExtend(const DeviceInfo& info) const
	{
		return info.swapChainSupport.capabilities.currentExtent;
	}

	VkSurfaceTransformFlagBitsKHR SwapchainSimplifier::GetImageTransform(const DeviceInfo& info) const
	{
		return info.swapChainSupport.capabilities.currentTransform;
	}

	void SwapchainSimplifier::DestroySwapchain()
	{
		if (_swapchain != VK_NULL_HANDLE)
		{
			for (size_t i = 0; i < _swapchainImageViews.size(); ++i)
			{
				vkDestroyImageView(_swapchainDevice, _swapchainImageViews[i], nullptr);
			}
			_swapchainImageViews.clear();
			_swapchainImages.clear();

			vkDestroySwapchainKHR(_swapchainDevice, _swapchain, nullptr);
			_swapchain = VK_NULL_HANDLE;
		}
	}

	void SwapchainSimplifier::GetSwapchainImages()
	{
		uint32_t imagesAmount = 0;

		vkGetSwapchainImagesKHR(_swapchainDevice, _swapchain, &imagesAmount, nullptr);

		_swapchainImages.resize(imagesAmount);

		vkGetSwapchainImagesKHR(_swapchainDevice, _swapchain, &imagesAmount, _swapchainImages.data());

		CreateSwapchainImageViews();
	}

	void SwapchainSimplifier::CreateSwapchainImageViews()
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = _swapchainFormat;

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

			if (vkCreateImageView(_swapchainDevice, &createInfo, nullptr, &_swapchainImageViews[i]) != VK_SUCCESS)
				throw std::runtime_error("DevicesSwapchainSimplifier::CreateSwapchainImageViews Error: Program failed to create a view for a swapchain image!");
		}
	}

	void SwapchainSimplifier::CreateSwapchain(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings)
	{
		if (_swapchain != VK_NULL_HANDLE)
			throw std::runtime_error("DevicesSwapchainSimplifier::CreateSwapchain Error: Program tried to create already existing swapchain!");

		_swapchainDevice = device;

		VkSwapchainCreateInfoKHR createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;

		_swapchainFormat = GetSwapchainFormat(settings.format, info.first);
		createInfo.imageFormat = _swapchainFormat;
		createInfo.imageColorSpace = colorspace;
		createInfo.imageArrayLayers = 1;
		_swapchainExtend = GetImageExtend(info.first);
		createInfo.imageExtent = _swapchainExtend;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.minImageCount = GetSwapchainImageAmount(settings.imageAmount, info.first.swapChainSupport.capabilities.minImageCount, info.first.swapChainSupport.capabilities.maxImageCount);

		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;

		createInfo.presentMode = GetSwapchainPresentMode(settings.presentMode, info.second);
		createInfo.preTransform = GetImageTransform(info.first);

		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("DevicesSwapchainSimplifier::CreateSwapchain Error: Program failed to create a swapchain!");
		}

		GetSwapchainImages();
	}

	SwapchainSimplifier::SwapchainSimplifier(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings)
	{
		_swapchain = VK_NULL_HANDLE;
		_swapchainDevice = VK_NULL_HANDLE;
		_swapchainFormat = VK_FORMAT_MAX_ENUM;
		_swapchainExtend = { 0, 0 };

		CreateSwapchain(device, surface, info, settings);
	}

	SwapchainSimplifier::~SwapchainSimplifier()
	{
		DestroySwapchain();
	}

	void SwapchainSimplifier::RecreateSwapchain(VkDevice device, VkSurfaceKHR surface, const std::pair<DeviceInfo, SimplifiedDeviceInfo>& info, SwapchainSettings settings)
	{
		DestroySwapchain();

		CreateSwapchain(device, surface, info, settings);
	}

}