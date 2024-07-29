export module VulkanSimplifiers.Common.StandardNonVulkanVersion;

import std;

export struct NonVulkanVersionData
{
	std::uint64_t major;
	std::uint64_t minor;
	std::uint64_t patch;
	std::uint64_t variation;

	NonVulkanVersionData();
};