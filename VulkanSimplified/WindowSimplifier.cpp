#include "pch.h"
#include "WindowSimplifier.h"

#include "Include/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	WindowSimplifier::WindowSimplifier(WindowCreationData data)
	{
		_window = CreateWindow(data);
	}

	WindowSimplifier::~WindowSimplifier()
	{
		DestroyWindow();
	}

	SDL_Window* WindowSimplifier::GetWindow() const
	{
		return _window;
	}

	SDL_Window* WindowSimplifier::CreateWindow(WindowCreationData data) const
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

	void WindowSimplifier::DestroyWindow()
	{
		if (_window != nullptr)
		{
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}
}
