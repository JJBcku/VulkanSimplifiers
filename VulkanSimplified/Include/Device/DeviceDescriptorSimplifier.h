#pragma once

namespace VulkanSimplified
{
	class DeviceDescriptorSimplifierInternal;

	class AutoCleanUpDescriptorPool;

	template<class T>
	class ListObjectID;

	enum class PipelineLayoutDescriptorType : uint64_t;

	class DeviceDescriptorSimplifier
	{
		DeviceDescriptorSimplifierInternal& _internal;

	public:
		DeviceDescriptorSimplifier(DeviceDescriptorSimplifierInternal& ref);
		~DeviceDescriptorSimplifier();

		DeviceDescriptorSimplifier(const DeviceDescriptorSimplifier&) noexcept = delete;

		DeviceDescriptorSimplifier& operator=(const DeviceDescriptorSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanUpDescriptorPool> AddDescriptorPool(const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes, uint64_t maxTotalSets,
			bool freeIndividual);
	};
}
