#pragma once

namespace VulkanSimplified
{
	class DeviceDescriptorSimplifierInternal;

	class AutoCleanupDescriptorSetLayout;

	class AutoCleanupDescriptorPool;
	class UniformBufferDescriptorSet;

	struct DescriptorSetUniformBufferWriteOrder;
	struct DescriptorSetUniformBufferCopyOrder;

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

		ListObjectID<AutoCleanupDescriptorPool> AddDescriptorPool(const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes, uint64_t maxTotalSets,
			bool freeIndividual);

		std::vector<ListObjectID<UniformBufferDescriptorSet>> AddUniformBuffers(ListObjectID<AutoCleanupDescriptorPool> poolID,
			const std::vector<ListObjectID<AutoCleanupDescriptorSetLayout>>& descriptorLayoutIDs);

		void UpdateUniformBufferDescriptorSets(const std::vector<DescriptorSetUniformBufferWriteOrder>& writeOrders,
			const std::vector<DescriptorSetUniformBufferCopyOrder>& copyOrders);
	};
}
