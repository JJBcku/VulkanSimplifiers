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

		bool _minimized, _hidden, _quit, _resized;

		char cpadding[4];

		SDL_Window* CreateWindow(WindowCreationData data) const;
		void DestroyWindow();

		std::vector<SDL_Event> GetEvents() const;

	public:
		WindowSimplifierInternal(WindowCreationData data);
		~WindowSimplifierInternal();

		SDL_Window* GetWindow() const;

		uint32_t GetWindowWidth() const;
		uint32_t GetWindowHeight() const;

		void HandleEvents();

		bool GetQuit() const;
		bool GetPaused() const;
		bool GetResized();
	};
}