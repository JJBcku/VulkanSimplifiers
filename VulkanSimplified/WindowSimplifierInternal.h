#pragma once

namespace VulkanSimplified
{
	struct WindowCreationData;
	class WindowsListPosition;

	class WindowSimplifierInternal
	{
		SDL_Window* _window;
		size_t padding;

		VkSurfaceKHR _surface;

		SDL_Window* CreateWindow(WindowCreationData data) const;
		void DestroyWindow();

	public:
		WindowSimplifierInternal(WindowCreationData data);
		~WindowSimplifierInternal();

		SDL_Window* GetWindow() const;
	};
}