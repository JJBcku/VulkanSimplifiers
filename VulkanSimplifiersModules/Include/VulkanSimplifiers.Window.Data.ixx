export module VulkanSimplifiers.Window.Data;

import std;

export enum class WindowProperties : std::uint64_t
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
	size_t padding;
	std::int32_t windowWidth, windowHeight;

	WindowProperties properties;
};