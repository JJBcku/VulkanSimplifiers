export module VulkanSimplifiers.Core.Data;
export import VulkanSimplifiers.EventHandler.Data;

export import VulkanSimplifiers.Common.StandardNonVulkanVersion;

export struct CoreSimplifierInitData
{
	NonVulkanVersionData appVersion;
	std::string appTitle;
	std::string appVariantTitle;
	EventHandlerInitData eventHandlerData;
	size_t instancesListInitialCapacity;
	size_t windowsListInitialCapacity;

	CoreSimplifierInitData();
};