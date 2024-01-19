#pragma once

#include "Include/BasicsSimplifierSharedStructs.h"
#include "Include/BasicsSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	struct VersionArray;

	class VulkanCoreSimplifierInternal
	{
		VkInstance _instance;
		char extraPadding[sizeof(size_t)];
		VkDebugUtilsMessengerEXT _debugMessenger;

		std::vector<VkExtensionProperties> _availableExtensions;
		std::vector<VkLayerProperties> _availableLayers;
		uint32_t _usedVersion;

		bool _extendedSwapchainColorSpace;

		char padding[3];

		uint32_t GetMaximumAvailableVulkanVersion()  const;
		uint32_t ComputeVersionFromVesionArray(VersionArray version) const;

		void EnumerateInstanceExtensions();
		void EnumerateLayers();

		void CheckForOptionalExtensions();
		std::vector<const char*> ListRequestedExtensions() const;
		std::vector<const char*> ListRequestedLayers() const;

		void CheckForLayerAndExtensionAvailability(std::vector<const char*> requestedExt, std::vector<const char*> requestedLayers);

	public:
		VulkanCoreSimplifierInternal(AppData appSettings);
		~VulkanCoreSimplifierInternal();

		VkInstance GetInstance() const;
		uint32_t GetUsedApiVersion() const;
	};

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
#endif
}

