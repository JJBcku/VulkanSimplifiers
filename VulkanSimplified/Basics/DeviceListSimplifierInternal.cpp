#include "../Other/pch.h"
#include "DeviceListSimplifierInternal.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"
#include "BasicsSimplifierInternalStructs.h"

#include "VulkanCoreSimplifierInternal.h"
#include "SurfaceSimplifierInternal.h"
#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "../Device/DeviceDataListSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceScore::DeviceScore(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t deviceID, intmax_t score) : _scoringFunction(scoringFunction)
	{
		_deviceID = deviceID;
		_padding = 0;
		_score = score;
	}

	DeviceScore::DeviceScore(DeviceScore&& other) noexcept : _scoringFunction(other._scoringFunction)
	{
		_padding = 0;
		_score = other._score;
		_deviceID = other._deviceID;
	}

	DeviceScore& DeviceScore::operator=(DeviceScore&& other) noexcept
	{
		_scoringFunction = other._scoringFunction;
		_score = other._score;
		_deviceID = other._deviceID;

		return *this;
	}

	bool DeviceScore::operator==(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction) const
	{
		return _scoringFunction == scoringFunction;
	}

	size_t DeviceScore::GetDeviceID() const
	{
		return _deviceID;
	}

	std::strong_ordering DeviceScore::operator<=>(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction) const
	{
		return _scoringFunction <=> scoringFunction;
	}

	SwapChainSupportDetails DeviceListSimplifierInternal::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const
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

	QueueFamilies DeviceListSimplifierInternal::QueryFamiliesSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const
	{
		QueueFamilies ret;

		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (size_t i = 0; i < queueFamilies.size(); ++i)
		{
			auto& queue = queueFamilies[i];

			if ((queue.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT && !(ret.graphicsFamily.has_value()))
			{
				VkBool32 presentSupport;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, static_cast<uint32_t>(i), surface, &presentSupport);

				if (presentSupport == VK_TRUE)
				{
					ret.graphicsFamily = static_cast<uint32_t>(i);
				}
			}
			else if ((queue.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT && !(ret.computeFamily.has_value()))
			{
				ret.computeFamily = static_cast<uint32_t>(i);
			}
			else if ((queue.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT && !(ret.transferFamily.has_value()))
			{
				ret.transferFamily = static_cast<uint32_t>(i);
			}

			if (ret.graphicsFamily.has_value() && ret.computeFamily.has_value() && ret.transferFamily.has_value())
				break;
		}

		return ret;
	}

	DeviceProperties DeviceListSimplifierInternal::QueryDeviceProperties(VkPhysicalDevice device) const
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

	DeviceFeatures DeviceListSimplifierInternal::QueryDeviceFeatures(VkPhysicalDevice device) const
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

	void DeviceListSimplifierInternal::EnumeratePhysicalDevices()
	{
		auto instance = _coreSimplifier.GetInstance();
		auto surface = _surfaceSimplifier.GetSurface();

		uint32_t deviceListSize = 0;
		std::vector<VkPhysicalDevice> availableDevices;

		vkEnumeratePhysicalDevices(instance, &deviceListSize, nullptr);
		availableDevices.resize(deviceListSize);
		_deviceList.reserve(deviceListSize);
		vkEnumeratePhysicalDevices(instance, &deviceListSize, availableDevices.data());

		std::vector<DeviceInfo> deviceList(availableDevices.size());

		for (size_t i = 0; i < availableDevices.size(); ++i)
		{
			auto& device = availableDevices[i];
			auto& info = deviceList[i];

			info.device = device;

			info.swapChainSupport = QuerySwapChainSupport(device, surface);
			info.queueFamilies = QueryFamiliesSupport(device, surface);
			info.features = QueryDeviceFeatures(device);
			info.properties = QueryDeviceProperties(device);
		}

		for (auto& device : deviceList)
		{
			_deviceList.emplace_back(SimplifyDeviceInfo(device), device.device);
		}
	}

	SimplifiedDeviceInfo DeviceListSimplifierInternal::SimplifyDeviceInfo(const DeviceInfo& deviceInfo) const
	{
		SimplifiedDeviceInfo ret;

		ret.deviceApiVersion = deviceInfo.properties.properties.apiVersion;

		ret.minSwapchainImages = deviceInfo.swapChainSupport.capabilities.minImageCount;
		ret.maxSwapchainImages = deviceInfo.swapChainSupport.capabilities.maxImageCount;

		ret.discreteGPU = deviceInfo.properties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

		auto& extensions = deviceInfo.properties.availableExtensions;
		for (size_t i = 0; i < extensions.size(); ++i)
		{
			if (strcmp(extensions[i].extensionName, VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME) == 0)
			{
				ret.unrestrictedDepth = true;

				if (ret.fillRectangleNV && ret.swapchainExtension)
					break;
			}
			else if (strcmp(extensions[i].extensionName, VK_NV_FILL_RECTANGLE_EXTENSION_NAME) == 0)
			{
				ret.fillRectangleNV = true;

				if (ret.unrestrictedDepth && ret.swapchainExtension)
					break;
			}
			else if (strcmp(extensions[i].extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
			{
				ret.swapchainExtension = true;

				if (ret.unrestrictedDepth && ret.fillRectangleNV)
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
				else if (formats[i].format == VK_FORMAT_A8B8G8R8_UNORM_PACK32)
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
				else if (formats[i].format == VK_FORMAT_B10G11R11_UFLOAT_PACK32)
				{
					ret.renderingColorList.OneAndHalfColor = true;
				}
				else if (formats[i].format == VK_FORMAT_R16G16B16A16_UNORM)
				{
					ret.renderingColorList.DoubleColor = true;
				}
			}
		}

		auto& presentModes = deviceInfo.swapChainSupport.presentModes;

		for (size_t i = 0; i < presentModes.size(); ++i)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				ret.mailboxPresentMode = true;
			}
			else if (presentModes[i] == VK_PRESENT_MODE_FIFO_KHR)
			{
				ret.fifoPresentMode = true;
			}
		}

		ret.queueFamilies = deviceInfo.queueFamilies;

		VkMemoryPropertyFlags deviceLocalMemoryProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		VkMemoryPropertyFlags externalUncachedMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VkMemoryPropertyFlags externalCachedCoherentMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VkMemoryPropertyFlags externalCachedIncoherentMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		VkMemoryPropertyFlags sharedUncachedMemoryProperties = deviceLocalMemoryProperties | externalUncachedMemoryProperties;
		VkMemoryPropertyFlags sharedCachedCoherentMemoryProperties = deviceLocalMemoryProperties | externalCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags sharedCachedIncoherentMemoryProperties = deviceLocalMemoryProperties | externalCachedIncoherentMemoryProperties;

		VkMemoryPropertyFlags deviceLocalMemoryRejectedProperties = externalCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags externalUncachedMemoryRejectedProperties = deviceLocalMemoryProperties | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		VkMemoryPropertyFlags externalCachedCoherentMemoryRejectedProperties = deviceLocalMemoryProperties;
		VkMemoryPropertyFlags externalCachedIncoherentMemoryRejectedProperties = deviceLocalMemoryProperties | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VkMemoryPropertyFlags sharedUncachedMemoryRejectedProperties = VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		VkMemoryPropertyFlags sharedCachedCoherentMemoryRejectedProperties = 0;
		VkMemoryPropertyFlags sharedCachedIncoherentMemoryRejectedProperties = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

		auto& memoryInfo = deviceInfo.properties.memory;
		for (uint32_t j = 0; j < memoryInfo.memoryTypeCount; ++j)
		{
			const VkMemoryHeap& heap = memoryInfo.memoryHeaps[memoryInfo.memoryTypes[j].heapIndex];
			const VkMemoryPropertyFlags& flags = memoryInfo.memoryTypes[j].propertyFlags;

			if ((heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
			{
				if ((flags & deviceLocalMemoryProperties) == deviceLocalMemoryProperties && (flags & deviceLocalMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.localMemorySize < heap.size)
					{
						ret.memoryHeapBiggestSizes.localMemorySize = heap.size;
					}
				}
				else if ((flags & sharedUncachedMemoryProperties) == sharedUncachedMemoryProperties && (flags & sharedUncachedMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.sharedMemory.uncached < heap.size)
					{
						ret.memoryHeapBiggestSizes.sharedMemory.uncached = heap.size;
					}
				}
				else if ((flags & sharedCachedCoherentMemoryProperties) == sharedCachedCoherentMemoryProperties && (flags & sharedCachedCoherentMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.sharedMemory.cachedCoherent < heap.size)
					{
						ret.memoryHeapBiggestSizes.sharedMemory.cachedCoherent = heap.size;
					}
				}
				else if ((flags & sharedCachedIncoherentMemoryProperties) == sharedCachedIncoherentMemoryProperties && (flags & sharedCachedIncoherentMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.sharedMemory.cachedIncoherent < heap.size)
					{
						ret.memoryHeapBiggestSizes.sharedMemory.cachedIncoherent = heap.size;
					}
				}
			}
			else if (heap.flags == 0)
			{
				if ((flags & externalUncachedMemoryProperties) == externalUncachedMemoryProperties && (flags & externalUncachedMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.externalMemory.uncached < heap.size)
					{
						ret.memoryHeapBiggestSizes.externalMemory.uncached = heap.size;
					}
				}
				else if ((flags & externalCachedCoherentMemoryProperties) == externalCachedCoherentMemoryProperties && (flags & externalCachedCoherentMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.externalMemory.cachedCoherent < heap.size)
					{
						ret.memoryHeapBiggestSizes.externalMemory.cachedCoherent = heap.size;
					}
				}
				else if ((flags & externalCachedIncoherentMemoryProperties) == externalCachedIncoherentMemoryProperties && (flags & externalCachedIncoherentMemoryRejectedProperties) == 0)
				{
					if (ret.memoryHeapBiggestSizes.externalMemory.cachedIncoherent < heap.size)
					{
						ret.memoryHeapBiggestSizes.externalMemory.cachedIncoherent = heap.size;
					}
				}
			}
		}

		return ret;
	}

	SimplifiedDeviceInfo DeviceListSimplifierInternal::GetSimplifiedDeviceInfo(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID, size_t position)
	{
		SimplifiedDeviceInfo ret;

		if (position >= _deviceList.size())
			throw std::runtime_error("DeviceListSimplifierInternal::GetSimplifiedDeviceInfo Error: Program tried to find device with position value bigger than the entire device list size!");

		auto it = std::find(_deviceScoresList.begin(), _deviceScoresList.end(), scoringFunctionID);

		if (it == _deviceScoresList.end())
			throw std::runtime_error("DeviceListSimplifierInternal::GetSimplifiedDeviceInfo Error: Program tried to find a device from an empty list of eligible devices!");

		size_t distance = static_cast<size_t>(std::distance(_deviceScoresList.begin(), it));
		size_t fullPosition = distance + position;

		if (fullPosition < distance)
			throw std::runtime_error("DeviceListSimplifierInternal::GetSimplifiedDeviceInfo Error: Position calculation overflow!");

		if (fullPosition >= _deviceScoresList.size() || _deviceScoresList[fullPosition] != scoringFunctionID)
			throw std::runtime_error("DeviceListSimplifierInternal::GetSimplifiedDeviceInfo Error: Program tried to find a device with position value bigger than the eligible scored devices list size!");

		ret = _deviceList[_deviceScoresList[fullPosition].GetDeviceID()].first;

		return ret;
	}

	size_t DeviceListSimplifierInternal::GetQualifyingDevicesAmount(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID)
	{
		size_t ret = 0;

		auto it = std::find(_deviceScoresList.cbegin(), _deviceScoresList.cend(), scoringFunctionID);

		if (it != _deviceScoresList.cend())
		{
			auto rit = std::find(_deviceScoresList.crbegin(), _deviceScoresList.crend(), scoringFunctionID);

			size_t distanceFirst = static_cast<size_t>(std::distance(_deviceScoresList.cbegin(), it));
			size_t distanceLast = static_cast<size_t>(std::distance(_deviceScoresList.cbegin(), rit.base()));

			ret = distanceLast - distanceFirst;
		}

		return ret;
	}

	ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> DeviceListSimplifierInternal::AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore)
	{
		auto ret = _scoringFunctions.AddObject(function);

		size_t neededCapacity = _deviceList.size() * _scoringFunctions.GetCapacity();

		if (_deviceScoresList.capacity() < neededCapacity)
			_deviceScoresList.reserve(neededCapacity);

		std::vector<DeviceScore> scoreList;
		scoreList.reserve(_deviceList.size());

		for (size_t i = 0; i < _deviceList.size(); ++i)
		{
			auto score = function(_deviceList[i].first);

			if (score >= minScore)
			{
				scoreList.emplace_back(ret, i, score);
			}
		}

		std::stable_sort(scoreList.begin(), scoreList.end());

		_deviceScoresList.insert(_deviceScoresList.cend(), scoreList.cbegin(), scoreList.cend());

		return ret;
	}

	ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> DeviceListSimplifierInternal::CreateDevice(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t position, DeviceSettings settings)
	{
		if (position >= _deviceList.size())
			throw std::runtime_error("DeviceListSimplifierInternal::CreateDevice Error: Program tried to create device with position value bigger than the entire device scores list size!");

		auto it = std::find(_deviceScoresList.begin(), _deviceScoresList.end(), scoringFunction);

		SimplifiedDeviceInfo createDeviceInfo;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		if (it == _deviceScoresList.end())
			throw std::runtime_error("DeviceListSimplifierInternal::CreateDevice Error: Program tried to create a device from an empty list of eligible devices!");

		size_t distance = static_cast<size_t>(std::distance(_deviceScoresList.begin(), it));
		size_t fullPosition = distance + position;

		if (fullPosition < distance)
			throw std::runtime_error("DeviceListSimplifierInternal::CreateDevice Error: Position calculation overflow!");

		if (fullPosition >= _deviceScoresList.size() || _deviceScoresList[fullPosition] != scoringFunction)
			throw std::runtime_error("DeviceListSimplifierInternal::CreateDevice Error: Program tried to create a device with position value bigger than the eligible scored devices list size!");

		createDeviceInfo = _deviceList[_deviceScoresList[fullPosition].GetDeviceID()].first;
		physicalDevice = _deviceList[_deviceScoresList[fullPosition].GetDeviceID()].second;

		auto ret = _logicalDevices.AddObject(std::make_unique<DeviceDataListSimplifierInternal>(physicalDevice, createDeviceInfo, settings, _sharedDataList, _swapchain));

		return ret;
	}

	const DeviceDataListSimplifierInternal& DeviceListSimplifierInternal::GetConstDeviceDataListSimplifier(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID) const
	{
		return *_logicalDevices.GetConstObject(deviceID);
	}

	DeviceDataListSimplifierInternal& DeviceListSimplifierInternal::GetDeviceDataListSimplifier(ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> deviceID)
	{
		return *_logicalDevices.GetObject(deviceID);
	}

	DeviceDataListSimplifierInternal& DeviceListSimplifierInternal::GetDeviceDataList(const ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>>& deviceID)
	{
		return *_logicalDevices.GetObject(deviceID);
	}

	constexpr size_t scoringFunctionReserve = 0x10;

	DeviceListSimplifierInternal::DeviceListSimplifierInternal(const VulkanCoreSimplifierInternal& coreSimplifier, const SurfaceSimplifierInternal& surfaceSimplifier,
		const SwapchainSimplifierInternal& swapchain, const SharedDataSimplifierCoreInternal& sharedDataList) : _coreSimplifier(coreSimplifier), _surfaceSimplifier(surfaceSimplifier),
		_swapchain(swapchain), _sharedDataList(sharedDataList), _scoringFunctions(scoringFunctionReserve)
	{

		_apiVersion = coreSimplifier.GetUsedApiVersion();
		assert(_apiVersion >= VK_MAKE_API_VERSION(0, 1, 0, 0));
		padding = 0;

		assert(coreSimplifier.GetInstance() != VK_NULL_HANDLE);
		assert(surfaceSimplifier.GetSurface() != VK_NULL_HANDLE);

		EnumeratePhysicalDevices();

		_deviceScoresList.reserve(_deviceList.size() * scoringFunctionReserve);
	}

	DeviceListSimplifierInternal::~DeviceListSimplifierInternal()
	{
		_logicalDevices.Reset();
	}

}