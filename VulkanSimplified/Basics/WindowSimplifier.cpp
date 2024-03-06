#include "../Other/pch.h"
#include "../Include/Basics/WindowSimplifier.h"

#include "WindowSimplifierInternal.h"

namespace VulkanSimplified
{

	WindowSimplifier::WindowSimplifier(WindowSimplifierInternal& ref) : _internal(ref)
	{
	}

	WindowSimplifier::~WindowSimplifier()
	{
	}

	void WindowSimplifier::HandleEvents()
	{
		_internal.HandleEvents();
	}

	bool WindowSimplifier::GetQuit() const
	{
		return _internal.GetQuit();
	}

	bool WindowSimplifier::GetPaused() const
	{
		return _internal.GetPaused();
	}

	bool WindowSimplifier::GetResized() const
	{
		return _internal.GetResized();
	}

}
