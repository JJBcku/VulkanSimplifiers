#pragma once

#include "BasicsSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	using IDType = uint64_t;

	struct VersionArray
	{
		uint16_t major, minor, patch, variant;
	};

	struct AppData
	{
		const char* appTitle;
		VersionArray appVersion;
		VersionArray minVulkanVersion;
		VersionArray maxVulkanVersion;

		const char* engineTitle;
		VersionArray engineVersion;
		//char padding[4];
	};

	struct WindowCreationData
	{
		const char* windowTitle;
		size_t padding;
		int32_t windowWidth, windowHeight;

		WindowProperties properties;
	};

	struct AvailableColorsList
	{
		bool NormalColor, HDRColor, OneAndHalfColor, DoubleColor;

		AvailableColorsList();
	};

	struct AvailableCompressedTexturesList
	{
		bool bc, etc2ANDeac, astc_LDR, astc_HDR;

		AvailableCompressedTexturesList();
	};

	struct QueueFamilies
	{
		std::optional<uint32_t> graphicsFamily, computeFamily, transferFamily, padding;

		QueueFamilies();
	};
	
	struct MemoryHeapSizes
	{
		uint64_t externalUncachedDeviceAccessibleMemorySize, externalCachedCoherentDeviceAccessibleMemorySize, externalCachedIncoherentDeviceAccessibleMemorySize;
		uint64_t localMemorySize;
		uint64_t sharedUncachedMemorySize;
		uint64_t sharedCachedCoherentMemorySize;
		uint64_t sharedCachedIncoherentMemorySize;

		MemoryHeapSizes();
	};

	struct SimplifiedDeviceInfo
	{
		AvailableColorsList renderingColorList;
		//AvailableCompressedTexturesList compressedTexturesList;

		bool unrestrictedDepth, fillRectangleNV, swapchainExtension, discreteGPU;

		bool mailboxPresentMode, fifoPresentMode;

		char padding[2];

		uint32_t deviceApiVersion;
		//uint32_t upadding;

		uint32_t minSwapchainImages;
		uint32_t maxSwapchainImages;

		QueueFamilies queueFamilies;

		MemoryHeapSizes memoryHeapBiggestSizes;
		
		SimplifiedDeviceInfo();
	};
}
