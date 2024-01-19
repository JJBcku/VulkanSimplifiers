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

		if (computeQueue.has_value())
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

	SimplifiedDeviceInfo DeviceListSimplifier::SimplifyDeviceInfo(const DeviceInfo& deviceInfo) const
	{
		SimplifiedDeviceInfo ret;

		ret.deviceApiVersion = deviceInfo.properties.properties.apiVersion;
		ret.discreteGPU = deviceInfo.properties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

		auto& extensions = deviceInfo.properties.availableExtensions;
		for (size_t i = 0; i < extensions.size(); ++i)
		{
			if (strcmp(extensions[i].extensionName, VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME))
			{
				ret.unrestrictedDepth = true;
				break;
			}
		}

		VkFormatFeatureFlags requiredFormatFlags = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT | VK_FORMAT_FEATURE_TRANSFER_DST_BIT;
		requiredFormatFlags = requiredFormatFlags | VK_FORMAT_FEATURE_BLIT_SRC_BIT | VK_FORMAT_FEATURE_BLIT_DST_BIT;
		requiredFormatFlags = requiredFormatFlags | VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT | VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT;

		auto& formats = deviceInfo.swapChainSupport.formats;
		for (size_t i = 0; i < formats.size(); ++i)
		{
			VkFormatProperties formatProperties{};

			vkGetPhysicalDeviceFormatProperties(deviceInfo.device, formats[i].format, &formatProperties);

			if ((formatProperties.optimalTilingFeatures & requiredFormatFlags) != requiredFormatFlags)
				continue;

			if (formats[i].colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
			{
				if (formats[i].format == VK_FORMAT_R8G8B8A8_UNORM)
				{
					ret.renderingColorList.NormalColor = true;
				}
				else if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					ret.renderingColorList.NormalColor = true;
				}
				else if (formats[i].format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
				{
					ret.renderingColorList.HDRColor = true;
				}
				else if (formats[i].format == VK_FORMAT_A2R10G10B10_UNORM_PACK32)
				{
					ret.renderingColorList.HDRColor = true;
				}
				else if (formats[i].format == VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16)
				{
					ret.renderingColorList.OneAndHalfColor = true;
				}
				else if (formats[i].format == VK_FORMAT_R16G16B16A16_UNORM)
				{
					ret.renderingColorList.DoubleColor = true;
				}
			}
		}

		VkMemoryPropertyFlags deviceLocalMemoryProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		VkMemoryPropertyFlags NOTdeviceLocalMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VkMemoryPropertyFlags sharedMemoryMemoryProperties = deviceLocalMemoryProperties | NOTdeviceLocalMemoryProperties;

		VkMemoryPropertyFlags deviceLocalMemoryRejectedProperties = NOTdeviceLocalMemoryProperties | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		VkMemoryPropertyFlags NOTdeviceLocalMemoryRejectedProperties = deviceLocalMemoryProperties | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		VkMemoryPropertyFlags sharedMemoryMemoryRejectedProperties = VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

		auto& memoryInfo = deviceInfo.properties.memory;
		for (uint32_t i = 0; i < memoryInfo.memoryHeapCount; ++i)
		{
			for (uint32_t j = 0; j < memoryInfo.memoryTypeCount; ++j)
			{
				if (memoryInfo.memoryTypes[j].heapIndex != i)
					continue;

				if ((memoryInfo.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
				{
					if ((memoryInfo.memoryTypes[j].propertyFlags & deviceLocalMemoryProperties) == deviceLocalMemoryProperties && (memoryInfo.memoryTypes[j].propertyFlags & deviceLocalMemoryRejectedProperties) == 0)
					{
						if (ret.localMemorySize < memoryInfo.memoryHeaps[i].size)
						{
							ret.localMemorySize = memoryInfo.memoryHeaps[i].size;
						}
					}
					else if ((memoryInfo.memoryTypes[j].propertyFlags & sharedMemoryMemoryProperties) == sharedMemoryMemoryProperties && (memoryInfo.memoryTypes[j].propertyFlags & sharedMemoryMemoryRejectedProperties) == 0)
					{
						if (ret.sharedMemorySize < memoryInfo.memoryHeaps[i].size)
						{
							ret.sharedMemorySize = memoryInfo.memoryHeaps[i].size;
						}
					}
				}
				else if (memoryInfo.memoryHeaps[i].flags == 0 && (memoryInfo.memoryTypes[j].propertyFlags & NOTdeviceLocalMemoryProperties) == NOTdeviceLocalMemoryProperties && (memoryInfo.memoryTypes[j].propertyFlags & NOTdeviceLocalMemoryRejectedProperties) == 0)
				{
					if (ret.nonLocalMemorySize < memoryInfo.memoryHeaps[i].size)
					{
						ret.nonLocalMemorySize = memoryInfo.memoryHeaps[i].size;
					}
				}
			}
		}

		return ret;
	}

	constexpr size_t scoringFunctionReserve = 0x10;

	DeviceListSimplifier::DeviceListSimplifier(uint32_t apiVersion, VkInstance instance, VkSurfaceKHR surface) : _scoringFunctions(scoringFunctionReserve)
	{
		_apiVersion = apiVersion;
		padding = 0;
		EnumeratePhysicalDevices(instance, surface);

		_deviceScoresList.reserve(_deviceList.size() * scoringFunctionReserve);
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