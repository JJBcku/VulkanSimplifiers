#include "../Other/pch.h"
#include "../Include/Device/DeviceDescriptorSimplifier.h"

#include "DeviceDescriptorSimplifierInternal.h"

#include "../Include/Common/ListObjectID.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{

	DeviceDescriptorSimplifier::DeviceDescriptorSimplifier(DeviceDescriptorSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceDescriptorSimplifier::~DeviceDescriptorSimplifier()
	{
	}

	ListObjectID<AutoCleanupDescriptorPool> DeviceDescriptorSimplifier::AddDescriptorPool(const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes,
		uint64_t maxTotalSets, bool freeIndividual)
	{
		return _internal.AddDescriptorPool(descriptorSetTypes, maxTotalSets, freeIndividual);
	}

	std::vector<ListObjectID<UniformBufferDescriptorSet>> DeviceDescriptorSimplifier::AddUniformBuffers(ListObjectID<AutoCleanupDescriptorPool> poolID,
		const std::vector<ListObjectID<AutoCleanupDescriptorSetLayout>>& descriptorLayoutIDs)
	{
		return _internal.AddUniformBuffers(poolID, descriptorLayoutIDs);
	}

}