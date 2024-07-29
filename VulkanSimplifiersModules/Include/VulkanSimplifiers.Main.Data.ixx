export module VulkanSimplifiers.Main.Data;
export import VulkanSimplifiers.EventHandling.Data;

export import VulkanSimplifiers.Common.StandardNonVulkanVersion;

export struct MainSimplifierInitData
{
	NonVulkanVersionData appVersion;
	std::string appTitle;
	std::string appVariantTitle;
	EventHandlerInitData eventHandlerData;
	size_t instancesListInitialCapacity;
	size_t windowsListInitialCapacity;

	MainSimplifierInitData();
};