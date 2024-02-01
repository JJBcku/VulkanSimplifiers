#include "../pch.h"
#include "WindowSimplifierInternal.h"

#include "../Include/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	WindowSimplifierInternal::WindowSimplifierInternal(WindowCreationData data)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_width = static_cast<uint32_t>(data.windowWidth);
		_height = static_cast<uint32_t>(data.windowHeight);

		_window = CreateWindow(data);
		padding = 0;
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
