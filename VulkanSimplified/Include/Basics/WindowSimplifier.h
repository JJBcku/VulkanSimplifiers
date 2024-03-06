#pragma once

namespace VulkanSimplified
{
	class WindowSimplifierInternal;

	class WindowSimplifier
	{
		WindowSimplifierInternal& _internal;

	public:
		WindowSimplifier(WindowSimplifierInternal& ref);
		~WindowSimplifier();

		WindowSimplifier& operator=(const WindowSimplifier&) noexcept = delete;

		void HandleEvents();

		bool GetQuit() const;
		bool GetPaused() const;
		bool GetResized() const;
	};
}
