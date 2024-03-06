#pragma once

namespace VulkanSimplified
{
	enum class WindowProperties : uint64_t
	{
		NONE = 0,
		RESIZABLE = 1,
		BORDERLESS = 2,
		FULLSCREEN = 4,
		FULSCREEN_BORDERLESS = 8
	};
}