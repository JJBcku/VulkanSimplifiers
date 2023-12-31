#pragma once

#include "BasicSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class VulkanCoreSimplifier;
	class WindowSimplifier;

	class BasicsSimplifier
	{
		std::unique_ptr<VulkanCoreSimplifier> _core;
		std::unique_ptr<WindowSimplifier> _windows;

	public:
		BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;
	};
}

