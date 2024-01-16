#pragma once

namespace VulkanSimplified
{
	struct WindowCreationData;
	class WindowsListPosition;

	class WindowSimplifier
	{
		SDL_Window* _window;
		size_t padding;

		VkSurfaceKHR _surface;

		SDL_Window* CreateWindow(WindowCreationData data) const;
		void DestroyWindow();

	public:
		WindowSimplifier(WindowCreationData data);
		~WindowSimplifier();

		SDL_Window* GetWindow() const;
	};
}