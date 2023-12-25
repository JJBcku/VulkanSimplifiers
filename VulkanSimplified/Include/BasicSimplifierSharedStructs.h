#pragma once

struct AppData
{
	const char* appTitle;
	uint32_t appVersion;
	uint32_t minVulkanVersion;
};

struct WindowData
{
	const char* windowTitle;
	int32_t windowWidth, windowHeight;
};