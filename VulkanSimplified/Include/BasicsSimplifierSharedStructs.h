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

	struct SimplifiedDeviceInfo
	{
		AvailableColorsList renderingColorList;
		//AvailableCompressedTexturesList compressedTexturesList;

		bool unrestrictedDepth, fillRectangleNV, swapchainExtension, discreteGPU;

		bool mailboxPresentMode, fifoPresentMode;

		char padding[2];

		uint32_t deviceApiVersion;
		//uint32_t upadding;

		QueueFamilies queueFamilies;

		uint64_t nonLocalMemorySize, localMemorySize, sharedMemorySize;
		
		SimplifiedDeviceInfo();
	};
}