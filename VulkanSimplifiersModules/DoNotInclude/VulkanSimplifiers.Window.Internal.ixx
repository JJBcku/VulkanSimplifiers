module;

#include <SDL2/SDL.h>

export module VulkanSimplifiers.Window.Internal;

import VulkanSimplifiers.Window.Data;
import std;

export class WindowInternal
{
public:
	WindowInternal(WindowCreationData data);
	~WindowInternal();

	WindowInternal(const WindowInternal&) = delete;
	WindowInternal(WindowInternal&& other);

	WindowInternal& operator=(const WindowInternal&) = delete;
	WindowInternal& operator=(WindowInternal&& other);

	bool GetQuit() const;
	bool GetPaused() const;
	bool GetResized();

private:
	SDL_Window* _window;
	std::size_t _padding;

	std::uint32_t _width, _height;

	bool _minimized, _hidden, _quit, _resized;

	char _cpadding[4];

	void CreateWindow(WindowCreationData data);
	void DestroyWindow();
};
