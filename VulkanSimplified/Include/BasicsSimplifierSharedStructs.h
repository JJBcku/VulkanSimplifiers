#pragma once

#include "BasicsSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	using IDType = uint64_t;

	struct VersionArray
	{
		uint8_t major, minor, patch, variant;
	};

	struct AppData
	{
		const char* appTitle;
		VersionArray appVersion;
		VersionArray minVulkanVersion;

		const char* engineTitle;
		VersionArray engineVersion;
		char padding[4];
	};

	enum class WindowProperties : size_t
	{
		NONE = 0,
		RESIZABLE = 1,
		BORDERLESS = 2,
		FULLSCREEN = 4,
		FULSCREEN_BORDERLESS = 8
	};

	struct WindowCreationData
	{
		const char* windowTitle;
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

	struct SimplifiedDeviceInfo
	{
		AvailableColorsList renderingColorList;
		//AvailableCompressedTexturesList compressedTexturesList;

		bool unrestrictedDepth, discreteGPU;

		char padding[2];

		uint32_t deviceApiVersion;
		uint32_t upadding;

		uint64_t nonLocalMemorySize, localMemorySize, sharedMemorySize;
		
		SimplifiedDeviceInfo();
	};
}
