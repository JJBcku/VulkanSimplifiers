module VulkanSimplifiers.WindowList;

WindowListSimplifier::WindowListSimplifier(WindowListInternal& ref) : _internal(ref)
{
}

WindowListSimplifier::~WindowListSimplifier()
{
}

IDObject<WindowPointer> WindowListSimplifier::CreateWindow(WindowCreationData data, size_t addOnReservation)
{
	return _internal.CreateWindow(data, addOnReservation);
}

WindowSimplifier WindowListSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	return _internal.GetWindowSimplifier(windowID);
}

const WindowSimplifier WindowListSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID) const
{
	return _internal.GetWindowSimplifier(windowID);
}
