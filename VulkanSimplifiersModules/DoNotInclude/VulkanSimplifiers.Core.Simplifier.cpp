module;

module VulkanSimplifiers.Core.Simplifier;

CoreSimplifier::CoreSimplifier(size_t callbackListInitialCapacity, size_t reserveInstances, size_t reserveWindows)
{
	_internal = std::make_unique<CoreInternal>(callbackListInitialCapacity, reserveInstances, reserveWindows);
}

CoreSimplifier::~CoreSimplifier()
{
}

IDObject<WindowPointer> CoreSimplifier::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _internal->CreateWindow(data, addReserved);
}

EventHandlerSimplifier CoreSimplifier::GetEventHandler()
{
	return _internal->GetEventHandler();
}

WindowSimplifier CoreSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	return _internal->GetWindowSimplifier(windowID);
}
