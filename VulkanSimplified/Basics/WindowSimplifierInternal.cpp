#include "../Other/pch.h"
#include "WindowSimplifierInternal.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	WindowSimplifierInternal::WindowSimplifierInternal(WindowCreationData data)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_width = static_cast<uint32_t>(data.windowWidth);
		_height = static_cast<uint32_t>(data.windowHeight);

		_window = CreateWindow(data);
		padding = 0;

		_minimized = false;
		_hidden = false;
		_quit = false;
		_resized = false;
	}

	WindowSimplifierInternal::~WindowSimplifierInternal()
	{
		DestroyWindow();
		SDL_Quit();
	}

	SDL_Window* WindowSimplifierInternal::GetWindow() const
	{
		return _window;
	}

	uint32_t WindowSimplifierInternal::GetWindowWidth() const
	{
		return _width;
	}

	uint32_t WindowSimplifierInternal::GetWindowHeight() const
	{
		return _height;
	}

	std::vector<SDL_Event> WindowSimplifierInternal::GetEvents() const
	{
		std::vector<SDL_Event> ret;
		ret.reserve(0x10);
		SDL_Event event{};

		while (SDL_PollEvent(&event) != 0)
		{
			if (ret.size() == ret.capacity())
				ret.reserve(ret.capacity() << 1);

			ret.push_back(event);
		}

		return ret;
	}

	void WindowSimplifierInternal::HandleEvents()
	{
		auto events = GetEvents();

		for (auto& event : events)
		{
			if (event.type == SDL_QUIT)
			{
				_quit = true;
			}
			else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				_quit = true;
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SHOWN:
					_hidden = false;
					_minimized = false;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					_hidden = true;
					break;
				case SDL_WINDOWEVENT_RESIZED:
					_resized = true;
					_width = static_cast<uint32_t>(event.window.data1);
					_height = static_cast<uint32_t>(event.window.data2);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					_minimized = true;
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					_minimized = false;
					_hidden = false;
					break;
				case SDL_WINDOWEVENT_RESTORED:
					_minimized = false;
					_hidden = false;
					break;
				default:
					break;
				}
			}
		}
	}

	bool WindowSimplifierInternal::GetQuit() const
	{
		return _quit;
	}

	bool WindowSimplifierInternal::GetPaused() const
	{
		return _minimized || _hidden;
	}

	bool WindowSimplifierInternal::GetResized()
	{
		bool ret = _resized;
		_resized = false;

		return ret;
	}

	SDL_Window* WindowSimplifierInternal::CreateWindow(WindowCreationData data) const
	{
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

		SDL_Window* window = SDL_CreateWindow(data.windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, data.windowWidth, data.windowHeight, flags);

		if (window == nullptr)
			throw std::runtime_error("Error: Program failed to create a window!");

		return window;
	}

	void WindowSimplifierInternal::DestroyWindow()
	{
		if (_window != nullptr)
		{
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}
}
