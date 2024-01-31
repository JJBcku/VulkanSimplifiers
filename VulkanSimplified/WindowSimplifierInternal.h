#pragma once

namespace VulkanSimplified
{
	struct WindowCreationData;
	class WindowsListPosition;

	class WindowSimplifierInternal
	{
		SDL_Window* _window;
		size_t padding;

		uint32_t _width, _height;

		SDL_Window* CreateWindow(WindowCreationData data) const;
		void DestroyWindow();

	public:
		WindowSimplifierInternal(WindowCreationData data);
		~WindowSimplifierInternal();

		SDL_Window* GetWindow() const;

		uint32_t GetWindowWidth() const;
		uint32_t GetWindowHeight() const;
	};
}