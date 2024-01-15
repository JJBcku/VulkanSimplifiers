#pragma once

#include "BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class VulkanCoreSimplifier;
	class WindowSimplifier;
	class SurfaceSimplifier;

	struct WindowCreationData;
	struct AppData;

	class BasicsSimplifier
	{
		std::unique_ptr<VulkanCoreSimplifier> _core;
		std::unique_ptr<WindowSimplifier> _windows;
		std::unique_ptr<SurfaceSimplifier> _surface;

	public:
		BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;
	};
}

