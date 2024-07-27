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

export struct WindowCreationData
{
	const char* windowTitle = nullptr;
	std::int32_t windowWidth = 0;
	std::int32_t windowHeight = 0;

	WindowProperties properties = WindowProperties::NONE;
};