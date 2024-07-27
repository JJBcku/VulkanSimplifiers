module;

module VulkanSimplifiers.Core.Simplifier;

CoreSimplifier::CoreSimplifier(const CoreSimplifierInitData& initData)
{
	_internal = std::make_unique<CoreInternal>(initData);
}

CoreSimplifier::~CoreSimplifier()
{
}

EventHandlingSimplifier CoreSimplifier::GetEventHandler()
{
	return _internal->GetEventHandler();
}

WindowListSimplifier CoreSimplifier::GetWindowListSimplifier()
{
	return _internal->GetWindowListSimplifier();
}
