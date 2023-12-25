#pragma once

#include "BasicSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class WindowSimplifier;

	class BasicsSimplifier
	{
		std::unique_ptr<WindowSimplifier> _windows;

	public:
		BasicsSimplifier(WindowCreationData data);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;
	};
}

