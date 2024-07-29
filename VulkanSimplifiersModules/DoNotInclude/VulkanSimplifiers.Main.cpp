module;

module VulkanSimplifiers.Main;

MainSimplifier::MainSimplifier(const MainSimplifierInitData& initData)
{
	_internal = std::make_unique<MainInternal>(initData);
}

MainSimplifier::~MainSimplifier()
{
}

EventHandlingSimplifier MainSimplifier::GetEventHandler()
{
	return _internal->GetEventHandler();
}

WindowListSimplifier MainSimplifier::GetWindowListSimplifier()
{
	return _internal->GetWindowListSimplifier();
}
