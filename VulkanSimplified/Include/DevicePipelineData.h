#pragma once

#include "DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class DevicePipelineDataInternal;
	class AutoCleanupDescriptorSetLayout;

	class DevicePipelineData
	{
		DevicePipelineDataInternal& _internal;

	public:
		DevicePipelineData(DevicePipelineDataInternal& ref);
		~DevicePipelineData();

		DevicePipelineData& operator=(const DevicePipelineData&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList);
	};
}
