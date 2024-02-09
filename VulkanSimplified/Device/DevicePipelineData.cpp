#include "../Other/pch.h"
#include "../Include/DevicePipelineData.h"

#include "DevicePipelineDataInternal.h"

namespace VulkanSimplified
{
	DevicePipelineData::DevicePipelineData(DevicePipelineDataInternal& ref) : _internal(ref)
	{
	}

	DevicePipelineData::~DevicePipelineData()
	{
	}

	ListObjectID<AutoCleanupDescriptorSetLayout> DevicePipelineData::AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList)
	{
		return _internal.AddDescriptorSetLayout(bindingsIDList);
	}
}