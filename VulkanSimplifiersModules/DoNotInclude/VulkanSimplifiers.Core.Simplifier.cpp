module;

module VulkanSimplifiers.Core.Simplifier;

CoreSimplifier::CoreSimplifier(size_t reserveInstances, size_t reserveWindows)
{
	_internal = std::make_unique<CoreInternal>(reserveInstances, reserveWindows);
}

CoreSimplifier::~CoreSimplifier()
{
}

IDObject<WindowPointer> CoreSimplifier::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _internal->CreateWindow(data, addReserved);
}

WindowSimplifier CoreSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	return _internal->GetWindowSimplifier(windowID);
}
