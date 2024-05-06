#pragma once

#include "../Other/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class BasicDescriptorSet
	{
		VkDescriptorSet _desciptorSet;

	public:
		BasicDescriptorSet(VkDescriptorSet descriptorSet);
		~BasicDescriptorSet();

		BasicDescriptorSet(const BasicDescriptorSet&) noexcept = default;
		BasicDescriptorSet(BasicDescriptorSet&& other) noexcept = default;

		BasicDescriptorSet& operator=(const BasicDescriptorSet&) noexcept = default;
		BasicDescriptorSet& operator=(BasicDescriptorSet&& other) noexcept = default;
	};

	enum class PipelineLayoutDescriptorType : uint64_t;

	class AutoCleanUpDescriptorPool
	{
		VkDescriptorPool _descriptorPool;
		VkDevice _device;

		uint32_t _maxSets;
		std::vector<std::pair<VkDescriptorPoolSize, uint64_t>> _setTypeSizes;

	public:
		AutoCleanUpDescriptorPool(VkDescriptorPool descriptorPool, VkDevice device, uint32_t maxSets, const std::vector<VkDescriptorPoolSize>& setTypeMaxSizes);
		~AutoCleanUpDescriptorPool();

		AutoCleanUpDescriptorPool(const AutoCleanUpDescriptorPool&) noexcept = delete;
		AutoCleanUpDescriptorPool(AutoCleanUpDescriptorPool&& other) noexcept;

		AutoCleanUpDescriptorPool& operator=(const AutoCleanUpDescriptorPool&) noexcept = delete;
		AutoCleanUpDescriptorPool& operator=(AutoCleanUpDescriptorPool&& other) noexcept;
	};

	class DeviceDescriptorSimplifierInternal
	{
		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanUpDescriptorPool> _descriptorPools;

		std::string GetPipelineLayoutDescriptorName(PipelineLayoutDescriptorType type) const;

	public:
		DeviceDescriptorSimplifierInternal(VkDevice device);
		~DeviceDescriptorSimplifierInternal();

		DeviceDescriptorSimplifierInternal(const DeviceDescriptorSimplifierInternal&) noexcept = delete;

		DeviceDescriptorSimplifierInternal& operator=(const DeviceDescriptorSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanUpDescriptorPool> AddDescriptorPool(const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes, uint64_t maxTotalSets,
			bool freeIndividual);
	};
}