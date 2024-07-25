module;

module VulkanSimplifiers.Core.Simplifier;

CoreSimplifier::CoreSimplifier(const CoreSimplifierInitData& initData)
{
	_internal = std::make_unique<CoreInternal>(initData);
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
