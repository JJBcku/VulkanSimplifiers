#pragma once

#include "../Other/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class BasicDescriptorSet
	{
	protected:
		VkDescriptorSet _desciptorSet;

	public:
		BasicDescriptorSet(VkDescriptorSet descriptorSet);
		~BasicDescriptorSet();

		BasicDescriptorSet(const BasicDescriptorSet&) noexcept = default;
		BasicDescriptorSet(BasicDescriptorSet&& other) noexcept = default;

		BasicDescriptorSet& operator=(const BasicDescriptorSet&) noexcept = default;
		BasicDescriptorSet& operator=(BasicDescriptorSet&& other) noexcept = default;

		VkDescriptorSet GetDescriptorSet() const;
	};

	class UniformBufferDescriptorSet : public BasicDescriptorSet
	{
	public:
		UniformBufferDescriptorSet(VkDescriptorSet descriptorSet);
		~UniformBufferDescriptorSet();

		UniformBufferDescriptorSet(const UniformBufferDescriptorSet&) noexcept = default;
		UniformBufferDescriptorSet(UniformBufferDescriptorSet&&) noexcept = default;

		UniformBufferDescriptorSet& operator=(const UniformBufferDescriptorSet&) noexcept = default;
		UniformBufferDescriptorSet& operator=(UniformBufferDescriptorSet&&) noexcept = default;
	};

	enum class PipelineLayoutDescriptorType : uint64_t;
	struct DescriptorSetUniformBufferWriteOrder;
	struct DescriptorSetUniformBufferCopyOrder;

	struct DescriptorSetUniformBufferWriteOrder;

	class AutoCleanupDescriptorPool
	{
		VkDescriptorPool _descriptorPool;
		VkDevice _device;
		bool _freeIndividual;
		char _padding[sizeof(size_t) - 1];

		uint32_t _maxSets;
		uint32_t _currentSets;
		std::vector<VkDescriptorPoolSize> _setTypeSizes;
		char padding[16 - (sizeof(_setTypeSizes) % 16)];

		ListTemplate<UniformBufferDescriptorSet> _uniformBuffers;

	public:
		AutoCleanupDescriptorPool(VkDescriptorPool descriptorPool, VkDevice device, uint32_t maxSets, bool freeIndividual, const std::vector<VkDescriptorPoolSize>& setTypeMaxSizes);
		AutoCleanupDescriptorPool(VkDescriptorPool descriptorPool, VkDevice device, uint32_t maxSets, bool freeIndividual, std::vector<VkDescriptorPoolSize>&& setTypeMaxSizes);
		~AutoCleanupDescriptorPool();

		AutoCleanupDescriptorPool(const AutoCleanupDescriptorPool&) noexcept = delete;
		AutoCleanupDescriptorPool(AutoCleanupDescriptorPool&& other) noexcept;

		AutoCleanupDescriptorPool& operator=(const AutoCleanupDescriptorPool&) noexcept = delete;
		AutoCleanupDescriptorPool& operator=(AutoCleanupDescriptorPool&& other) noexcept;

		std::vector<ListObjectID<UniformBufferDescriptorSet>> AddUniformBuffers(const std::vector<VkDescriptorSetLayout>& descriptorLayouts);

		VkDescriptorSet GetUniformBufferDescriptorSet(ListObjectID<UniformBufferDescriptorSet> _descriptorID) const;
	};

	class DevicePipelineDataInternal;
	class DeviceDataBufferSimplifierInternal;
	class AutoCleanupDescriptorSetLayout;

	struct UniformBufferDescriptorSetID;

	class DeviceDescriptorSimplifierInternal
	{
		VkDevice _device;
		void* _ppadding;

		const DevicePipelineDataInternal& _pipelineData;
		const DeviceDataBufferSimplifierInternal& _dataBuffers;

		ListTemplate<AutoCleanupDescriptorPool> _descriptorPools;

		std::string GetPipelineLayoutDescriptorName(PipelineLayoutDescriptorType type) const;

	public:
		DeviceDescriptorSimplifierInternal(VkDevice device, const DevicePipelineDataInternal& pipelineData, const DeviceDataBufferSimplifierInternal& dataBuffers);
		~DeviceDescriptorSimplifierInternal();

		DeviceDescriptorSimplifierInternal(const DeviceDescriptorSimplifierInternal&) noexcept = delete;

		DeviceDescriptorSimplifierInternal& operator=(const DeviceDescriptorSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorPool> AddDescriptorPool(const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes, uint64_t maxTotalSets,
			bool freeIndividual);

		std::vector<ListObjectID<UniformBufferDescriptorSet>> AddUniformBuffers(ListObjectID<AutoCleanupDescriptorPool> poolID,
			const std::vector<ListObjectID<AutoCleanupDescriptorSetLayout>>& descriptorLayoutIDs);

		void UpdateUniformBufferDescriptorSets(const std::vector<DescriptorSetUniformBufferWriteOrder>& writeOrders,
			const std::vector<DescriptorSetUniformBufferCopyOrder>& copyOrders);

		VkDescriptorSet GetUniformBufferDescriptorSet(UniformBufferDescriptorSetID descriptorID) const;
	};
}