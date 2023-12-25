#pragma once

namespace VulkanSimplified
{
	struct AppData
	{
		const char* appTitle;
		uint8_t appVersion[4];
		uint8_t minVulkanVersion[4];
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
}
