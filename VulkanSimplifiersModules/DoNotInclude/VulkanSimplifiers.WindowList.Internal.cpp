module VulkanSimplifiers.WindowList.Internal;

WindowListInternal::WindowListInternal(size_t initialListCapacity) : _windowList(initialListCapacity)
{
}

WindowListInternal::~WindowListInternal()
{
}

IDObject<WindowPointer> WindowListInternal::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _windowList.AddObject(std::make_unique<WindowInternal>(data), addReserved);
}

WindowInternal& WindowListInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetObject(windowID);

	return *window;
}

const WindowInternal& WindowListInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID) const
{
	auto& window = _windowList.GetConstObject(windowID);

	return *window;
}
