#pragma once

#include "BasicsSimplifierSharedEnums.h"

namespace VulkanSimplified
{
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
	};

	struct AvailableCompressedTexturesList
	{
		bool bc, etc2ANDeac, astc_LDR, astc_HDR;
	};

	struct SimplifiedDeviceInfo
	{
		AvailableColorsList renderingColorList;
		//AvailableCompressedTexturesList compressedTexturesList;

		bool unrestrictedDepth;
		
	};
}
