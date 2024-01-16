#pragma once

#include "BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;

	struct WindowCreationData;
	struct AppData;

	class BasicsSimplifier
	{
		std::unique_ptr<BasicsSimplifierInternal> _internal;

	public:
		BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings);
		~BasicsSimplifier();

		BasicsSimplifier(const BasicsSimplifier&) = delete;
		BasicsSimplifier& operator= (const BasicsSimplifier&) = delete;
	};
}

