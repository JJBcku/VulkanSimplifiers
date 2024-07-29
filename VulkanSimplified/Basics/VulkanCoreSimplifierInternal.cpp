#include "../Other/pch.h"
#include "VulkanCoreSimplifierInternal.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{

	uint32_t VulkanCoreSimplifierInternal::GetMaximumAvailableVulkanVersion() const
	{
#pragma warning(push)
#pragma warning(disable : 4191)

		uint32_t ret = 0;
		auto func = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(NULL, "vkEnumerateInstanceVersion"));
#pragma warning(pop)

		if (func == NULL)
		{
			ret = VK_API_VERSION_1_0;
		}
		else
		{
			func(&ret);
		}

		return ret;
	}

	uint32_t VulkanCoreSimplifierInternal::ComputeVersionFromVersionArray(VersionArray version)  const
	{
		return VK_MAKE_API_VERSION(version.variant, version.major, version.minor, version.patch);
	}

	void VulkanCoreSimplifierInternal::EnumerateInstanceExtensions()
	{
		uint32_t extCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);

		_availableExtensions.resize(extCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, _availableExtensions.data());
	}

	void VulkanCoreSimplifierInternal::EnumerateLayers()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		_availableLayers.resize(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, _availableLayers.data());
	}

	void VulkanCoreSimplifierInternal::CheckForOptionalExtensions()
	{
		for (const auto& ext : _availableExtensions)
		{
			if (strcmp(ext.extensionName, VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME) == 0)
			{
				_extendedSwapchainColorSpace = true;

				break;
			}
		}
	}

	std::vector<const char*> VulkanCoreSimplifierInternal::ListRequestedExtensions() const
	{
		std::vector<const char*> ret;

		unsigned int size = 0;
		SDL_Vulkan_GetInstanceExtensions(nullptr, &size, nullptr);

		ret.reserve(static_cast<size_t>(size) + 0x10);
		ret.resize(size);
		SDL_Vulkan_GetInstanceExtensions(nullptr, &size, ret.data());

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
		ret.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		if (_extendedSwapchainColorSpace)
			ret.push_back(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);

		return ret;
	}

	std::vector<const char*> VulkanCoreSimplifierInternal::ListRequestedLayers() const
	{
		std::vector<const char*> ret;

		ret.push_back("VK_LAYER_KHRONOS_validation");

		return ret;
	}

	void VulkanCoreSimplifierInternal::CheckForLayerAndExtensionAvailability(std::vector<const char*> requestedExt, std::vector<const char*> requestedLayers)
	{
		if (!requestedExt.empty())
		{
			std::vector<bool> _foundExtensions(requestedExt.size(), false);

			for (auto& extension : _availableExtensions)
			{
				bool allFound = false;

				for (size_t i = 0; i < requestedExt.size(); ++i)
				{
					if (!_foundExtensions[i] && strcmp(requestedExt[i], extension.extensionName) == 0)
					{
						_foundExtensions[i] = true;

						auto it = std::find(_foundExtensions.cbegin(), _foundExtensions.cend(), false);
						if (it == _foundExtensions.cend())
						{
							allFound = true;
							break;
						}
					}
				}

				if (allFound)
					break;
			}

			auto it = std::find(_foundExtensions.cbegin(), _foundExtensions.cend(), false);
			if (it != _foundExtensions.cend())
				throw std::runtime_error("Error: One or more of the requested vulkan instance extensions are unavailable!");
		}

		if (!requestedLayers.empty())
		{
			std::vector<bool> _foundLayers(requestedLayers.size(), false);

			for (auto& layer : _availableLayers)
			{
				bool allFound = false;

				for (size_t i = 0; i < requestedLayers.size(); ++i)
				{
					if (!_foundLayers[i] && strcmp(requestedLayers[i], layer.layerName) == 0)
					{
						_foundLayers[i] = true;

						auto it = std::find(_foundLayers.cbegin(), _foundLayers.cend(), false);
						if (it == _foundLayers.cend())
						{
							allFound = true;
							break;
						}
					}
				}

				if (allFound)
					break;
			}

			auto it = std::find(_foundLayers.cbegin(), _foundLayers.cend(), false);
			if (it != _foundLayers.cend())
				throw std::runtime_error("Error: One or more of the requested vulkan layers are unavailable!");
		}
	}

	VulkanCoreSimplifierInternal::VulkanCoreSimplifierInternal(AppData appSettings)
	{
		_usedVersion = GetMaximumAvailableVulkanVersion();
		_instance = VK_NULL_HANDLE;
		_debugMessenger = VK_NULL_HANDLE;
		_extendedSwapchainColorSpace = false;

		if (ComputeVersionFromVersionArray(appSettings.minVulkanVersion) > _usedVersion)
		{
			throw std::runtime_error("Error: Highest supported version is lower than minimum required version!");
		}

		uint32_t maxVersion = ComputeVersionFromVersionArray(appSettings.maxVulkanVersion);

		if (_usedVersion > maxVersion)
			_usedVersion = maxVersion;

		EnumerateInstanceExtensions();
		EnumerateLayers();

		auto requestedExtensions = ListRequestedExtensions();
		std::vector<const char*> requestedLayers;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
		requestedLayers = ListRequestedLayers();
#endif

		CheckForLayerAndExtensionAvailability(requestedExtensions, requestedLayers);

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.applicationVersion = ComputeVersionFromVersionArray(appSettings.appVersion);
		appInfo.pApplicationName = appSettings.appTitle;
		appInfo.pEngineName = "JJEngine";
		appInfo.engineVersion = ComputeVersionFromVersionArray(appSettings.engineVersion);
		appInfo.apiVersion = _usedVersion;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.pApplicationInfo = &appInfo;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size());
		createInfo.ppEnabledExtensionNames = requestedExtensions.empty() ? nullptr : requestedExtensions.data();
		createInfo.enabledLayerCount = static_cast<uint32_t>(requestedLayers.size());
		createInfo.ppEnabledLayerNames = requestedLayers.empty() ? nullptr : requestedLayers.data();
		createInfo.flags = 0;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
		VkDebugUtilsMessengerCreateInfoEXT debugInfo{};
		debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugInfo.pfnUserCallback = debugCallback;
		debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
		debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
		debugInfo.flags = 0;
		debugInfo.pNext = nullptr;
		debugInfo.pUserData = nullptr;

		createInfo.pNext = &debugInfo;
#endif

		if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Error: Program failed to create vulkan instance!");
		}

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
#pragma warning(push)
#pragma warning(disable : 4191)
		auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT"));
#pragma warning(pop)

		if (func == nullptr || func(_instance, &debugInfo, nullptr, &_debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("Error: Program failed to create a debug messenger!");
		}
#endif

	}

	VulkanCoreSimplifierInternal::~VulkanCoreSimplifierInternal()
	{
		if (_debugMessenger != VK_NULL_HANDLE)
		{
#pragma warning(push)
#pragma warning(disable : 4191)
			auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
#pragma warning(pop)

			if (func != nullptr)
				func(_instance, _debugMessenger, nullptr);
		}

		if (_instance != VK_NULL_HANDLE)
		{
			vkDestroyInstance(_instance, nullptr);
		}
	}

	VkInstance VulkanCoreSimplifierInternal::GetInstance() const
	{
		return _instance;
	}

	uint32_t VulkanCoreSimplifierInternal::GetUsedApiVersion() const
	{
		return _usedVersion;
	}

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void*)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
#endif

}
