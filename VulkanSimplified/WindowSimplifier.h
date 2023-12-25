#pragma once

namespace VulkanSimplified
{
	struct WindowCreationData;
	class WindowsListPosition;

	class WindowSimplifier
	{
		SDL_Window* _window;

		SDL_Window* CreateWindow(WindowCreationData data);
		void DestroyWindow();

	public:
		WindowSimplifier(WindowCreationData data);
		~WindowSimplifier();
	};
}