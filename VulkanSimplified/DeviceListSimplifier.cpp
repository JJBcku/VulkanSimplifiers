#include "pch.h"
#include "DeviceListSimplifier.h"

#include "Include/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{

	SwapChainSupportDetails DeviceListSimplifier::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const
	{
		SwapChainSupportDetails ret;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &ret.capabilities);

		uint32_t size;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &size, nullptr);

		if (size != 0)
		{
			ret.formats.resize(size);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &size, ret.formats.data());
		}

		size = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &size, nullptr);

		if (size != 0)
		{
			ret.presentModes.resize(size);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &size, ret.presentModes.data());
		}

		return ret;
	}

	QueueFamilies DeviceListSimplifier::QueryFamiliesSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const
	{
		QueueFamilies ret;

		std::optional<uint64_t> graphicQueue;
		std::optional<uint64_t> computeQueue;
		std::optional<uint64_t> tranferQueue;

		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (size_t i = 0; i < queueFamilies.size(); ++i)
		{
			auto& queue = queueFamilies[i];

			if ((queue.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT && !(graphicQueue.has_value()))
			{
				VkBool32 presentSupport;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, static_cast<uint32_t>(i), surface, &presentSupport);

				if (presentSupport == VK_TRUE)
				{
					graphicQueue = i;
				}
			}
			else if ((queue.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT && !(computeQueue.has_value()))
			{
				computeQueue = i;
			}
			else if ((queue.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT && !(tranferQueue.has_value()))
			{
				tranferQueue = i;
			}

			if (graphicQueue.has_value() && computeQueue.has_value() && tranferQueue.has_value())
				break;
		}

		if (graphicQueue.has_value())
		{
			ret.graphicsFamily = graphicQueue.value();
			ret.computeFamily = graphicQueue.value();
			ret.transferFamily = graphicQueue.value();
		}

		if (tranferQueue.has_value())
		{
			ret.transferFamily = computeQueue.value();
			ret.computeFamily = computeQueue.value();
		}

		if (tranferQueue.has_value())
			ret.transferFamily = tranferQueue.value();

		return ret;
	}

	DeviceProperties DeviceListSimplifier::QueryDeviceProperties(VkPhysicalDevice device) const
	{
		DeviceProperties ret;

		if (_apiVersion < VK_API_VERSION_1_1)
		{
			vkGetPhysicalDeviceProperties(device, &ret.properties);
		}
		else
		{
			VkPhysicalDeviceProperties2 get{};
			get.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
			get.pNext = &ret.properties11;
			ret.properties11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;

			if (_apiVersion >= VK_API_VERSION_1_2)
			{
				ret.properties11.pNext = &ret.properties12;
				ret.properties12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;

				if (_apiVersion >= VK_API_VERSION_1_3)
				{
					ret.properties12.pNext = &ret.properties13;
					ret.properties13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
				}
			}

			vkGetPhysicalDeviceProperties2(device, &get);
			ret.properties = get.properties;
		}

		vkGetPhysicalDeviceMemoryProperties(device, &ret.memory);

		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		ret.availableExtensions.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, ret.availableExtensions.data());

		return ret;
	}

	DeviceFeatures DeviceListSimplifier::QueryDeviceFeatures(VkPhysicalDevice device) const
	{
		DeviceFeatures ret;

		if (_apiVersion < VK_API_VERSION_1_1)
		{
			vkGetPhysicalDeviceFeatures(device, &ret.features);
		}
		else
		{
			VkPhysicalDeviceFeatures2 get{};
			get.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			get.pNext = &ret.features11;
			ret.features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;

			if (_apiVersion >= VK_API_VERSION_1_2)
			{
				ret.features11.pNext = &ret.features12;
				ret.features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

				if (_apiVersion >= VK_API_VERSION_1_3)
				{
					ret.features12.pNext = &ret.features13;
					ret.features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
				}
			}

			vkGetPhysicalDeviceFeatures2(device, &get);
			ret.features = get.features;
		}

		return ret;
	}

	void DeviceListSimplifier::EnumeratePhysicalDevices(VkInstance instance, VkSurfaceKHR surface)
	{
		uint32_t deviceListSize = 0;
		std::vector<VkPhysicalDevice> availableDevices;

		vkEnumeratePhysicalDevices(instance, &deviceListSize, nullptr);
		availableDevices.resize(deviceListSize);
		_deviceList.resize(deviceListSize);
		vkEnumeratePhysicalDevices(instance, &deviceListSize, availableDevices.data());

		for (size_t i = 0; i < availableDevices.size(); ++i)
		{
			auto& device = availableDevices[i];
			auto& info = _deviceList[i];

			info.device = device;

			info.swapChainSupport = QuerySwapChainSupport(device, surface);
			info.queueFamilies = QueryFamiliesSupport(device, surface);
			info.features = QueryDeviceFeatures(device);
			info.properties = QueryDeviceProperties(device);
		}
	}

	DeviceListSimplifier::DeviceListSimplifier(uint32_t apiVersion, VkInstance instance, VkSurfaceKHR surface)
	{
		_apiVersion = apiVersion;
		padding = 0;
		EnumeratePhysicalDevices(instance, surface);
	}

	DeviceListSimplifier::~DeviceListSimplifier()
	{

	}

	QueueFamilies::QueueFamilies()
	{
		graphicsFamily = std::numeric_limits<uint64_t>::max();
		computeFamily = std::numeric_limits<uint64_t>::max();
		transferFamily = std::numeric_limits<uint64_t>::max();
	}

	SwapChainSupportDetails::SwapChainSupportDetails()
	{
		capabilities = {};
		memset(padding, 0, sizeof(padding));
	}

	DeviceProperties::DeviceProperties()
	{
		properties = {};
		properties11 = {};
		properties12 = {};
		properties13 = {};

		memory = {};
	}

	DeviceFeatures::DeviceFeatures()
	{
		features = {};
		memset(padding, 0, sizeof(padding));
		features11 = {};
		features12 = {};
		features13 = {};
	}

	DeviceInfo::DeviceInfo() : swapChainSupport(), queueFamilies(), features(), properties()
	{
		padding = 0;
		device = VK_NULL_HANDLE;
	}

}