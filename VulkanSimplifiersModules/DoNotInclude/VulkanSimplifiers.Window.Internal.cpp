module;

#include <SDL2/SDL.h>

module VulkanSimplifiers.Window.Internal;

WindowInternal::WindowInternal(WindowCreationData data)
{
	_width = static_cast<uint32_t>(data.windowWidth);
	_height = static_cast<uint32_t>(data.windowHeight);
	
	_window = nullptr;
	CreateWindow(data);
	_padding = 0;

	_minimized = false;
	_hidden = false;
	_quit = false;
	_resized = false;

	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;
}

WindowInternal::~WindowInternal()
{
	DestroyWindow();
}

WindowInternal::WindowInternal(WindowInternal&& other) : _window(other._window), _padding(0), _width(other._width), _height(other._height), _minimized(other._minimized),
_hidden(other._hidden), _quit(other._quit), _resized(other._resized)
{
	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	other._window = nullptr;
	other._width = 0;
	other._height = 0;
	other._minimized = false;
	other._hidden = false;
	other._quit = false;
	other._resized = false;
}

WindowInternal& WindowInternal::operator=(WindowInternal&& other)
{
	_window = other._window;
	_padding = 0;
	_width = other._width;
	_height = other._height;
	_minimized = other._minimized;
	_hidden = other._hidden;
	_quit = other._quit;
	_resized = other._resized;
	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	other._window = nullptr;
	other._width = 0;
	other._height = 0;
	other._minimized = false;
	other._hidden = false;
	other._quit = false;
	other._resized = false;

	return *this;
}

bool WindowInternal::GetQuit() const
{
	return _quit;
}

bool WindowInternal::GetPaused() const
{
	return _minimized || _hidden;
}

bool WindowInternal::GetResized()
{
	bool ret = _resized;
	_resized = false;

	return ret;
}

void WindowInternal::CreateWindow(WindowCreationData data)
{
	if (_window != nullptr)
		throw std::runtime_error("Error: Program tried to create an already existing window!");

	Uint32 flags = SDL_WINDOW_VULKAN;

	switch (data.properties)
	{
	case WindowProperties::NONE:
		break;
	case WindowProperties::RESIZABLE:
		flags |= SDL_WINDOW_RESIZABLE;
		break;
	case WindowProperties::BORDERLESS:
		flags |= SDL_WINDOW_BORDERLESS;
		break;
	case WindowProperties::FULLSCREEN:
		flags |= SDL_WINDOW_FULLSCREEN;
		break;
	case WindowProperties::FULSCREEN_BORDERLESS:
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS;
		break;
	default:
		throw std::runtime_error("Error: Unknown window creation properties!");
	}

	_window = SDL_CreateWindow(data.windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, data.windowWidth, data.windowHeight, flags);

	if (_window == nullptr)
		throw std::runtime_error("Error: Program failed to create a window!");
}

void WindowInternal::DestroyWindow()
{
	if (_window != nullptr)
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
}
