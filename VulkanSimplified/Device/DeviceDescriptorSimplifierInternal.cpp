#include "../Other/pch.h"
#include "DeviceDescriptorSimplifierInternal.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"
#include "../Other/Utils.h"

#include "DevicePipelineDataInternal.h"

namespace VulkanSimplified
{

	AutoCleanupDescriptorPool::AutoCleanupDescriptorPool(VkDescriptorPool descriptorPool, VkDevice device, uint32_t maxSets, bool freeIndividual,
		const std::vector<VkDescriptorPoolSize>& setTypeMaxSizes) : _descriptorPool(descriptorPool), _device(device), _freeIndividual(freeIndividual),
		_maxSets(maxSets), _currentSets(0), _setTypeSizes(setTypeMaxSizes)
	{
		memset(_padding, 0, sizeof(_padding));
	}

	AutoCleanupDescriptorPool::AutoCleanupDescriptorPool(VkDescriptorPool descriptorPool, VkDevice device, uint32_t maxSets, bool freeIndividual,
		std::vector<VkDescriptorPoolSize>&& setTypeMaxSizes) : _descriptorPool(descriptorPool), _device(device), _freeIndividual(freeIndividual),
		_maxSets(maxSets), _currentSets(0), _setTypeSizes(std::move(setTypeMaxSizes))
	{
		memset(_padding, 0, sizeof(_padding));
	}

	AutoCleanupDescriptorPool::~AutoCleanupDescriptorPool()
	{
		if (_descriptorPool != VK_NULL_HANDLE)
			vkDestroyDescriptorPool(_device, _descriptorPool, nullptr);
	}

	AutoCleanupDescriptorPool::AutoCleanupDescriptorPool(AutoCleanupDescriptorPool&& other) noexcept : _descriptorPool(other._descriptorPool), _device(other._device),
		_freeIndividual(other._freeIndividual), _maxSets(other._maxSets), _currentSets(other._currentSets), _setTypeSizes(std::move(other._setTypeSizes))
	{
		memset(_padding, 0, sizeof(_padding));

		other._descriptorPool = VK_NULL_HANDLE;
		other._device = VK_NULL_HANDLE;
		other._freeIndividual = false;
		other._maxSets = 0;
		other._currentSets = 0;
	}

	AutoCleanupDescriptorPool& AutoCleanupDescriptorPool::operator=(AutoCleanupDescriptorPool&& other) noexcept
	{
		_descriptorPool = other._descriptorPool;
		_device = other._device;
		_freeIndividual = other._freeIndividual;
		memset(_padding, 0, sizeof(_padding));
		_maxSets = other._maxSets;
		_currentSets = other._currentSets;
		_setTypeSizes = std::move(other._setTypeSizes);

		other._descriptorPool = VK_NULL_HANDLE;
		other._device = VK_NULL_HANDLE;
		other._freeIndividual = false;
		other._maxSets = 0;
		other._currentSets = 0;

		return *this;
	}

	std::vector<ListObjectID<UniformBufferDescriptorSet>> AutoCleanupDescriptorPool::AddUniformBuffers(const std::vector<VkDescriptorSetLayout>& descriptorLayouts)
	{
		if (descriptorLayouts.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("AutoCleanUpDescriptorPool::AddUniformBuffers Error: descriptor layouts vector overlowed at size = " + std::to_string(descriptorLayouts.size()));

		std::vector<ListObjectID<UniformBufferDescriptorSet>> ret;
		std::vector<VkDescriptorSet> descriptorSets(descriptorLayouts.size(), VK_NULL_HANDLE);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = _descriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(descriptorLayouts.size());
		allocInfo.pSetLayouts = descriptorLayouts.data();

		if (vkAllocateDescriptorSets(_device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanUpDescriptorPool::AddUniformBuffers Error: Program failed to allocate " + std::to_string(descriptorLayouts.size()) + std::string(" descriptor sets!"));

		ret.reserve(descriptorLayouts.size());

		for (auto& set : descriptorSets)
		{
			ret.push_back(_uniformBuffers.AddObject(UniformBufferDescriptorSet(set)));
		}

		return ret;
	}

	BasicDescriptorSet::BasicDescriptorSet(VkDescriptorSet descriptorSet) : _desciptorSet(descriptorSet)
	{
	}

	BasicDescriptorSet::~BasicDescriptorSet()
	{
	}

	std::string DeviceDescriptorSimplifierInternal::GetPipelineLayoutDescriptorName(PipelineLayoutDescriptorType type) const
	{
		std::string ret;

		switch (type)
		{
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLER:
			ret = "SAMPLER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::COMBINED_SAMPLER:
			ret = "COMBINED_SAMPLER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::SAMPLED_IMAGE:
			ret = "SAMPLED_IMAGE";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_IMAGE:
			ret = "STORAGE_IMAGE";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_TEXEL_BUFFER:
			ret = "UNIFORM_TEXEL_BUFFER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_TEXEL_BUFFER:
			ret = "STORAGE_TEXEL_BUFFER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER:
			ret = "UNIFORM_BUFFER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER:
			ret = "STORAGE_BUFFER";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::UNIFORM_BUFFER_DYNAMIC:
			ret = "UNIFORM_BUFFER_DYNAMIC";
			break;
		case VulkanSimplified::PipelineLayoutDescriptorType::STORAGE_BUFFER_DYNAMIC:
			ret = "STORAGE_BUFFER_DYNAMIC";
			break;
		default:
			ret = "UNKNOWN";
			break;
		}

		return ret;
	}

	DeviceDescriptorSimplifierInternal::DeviceDescriptorSimplifierInternal(VkDevice device, DevicePipelineDataInternal& pipelineData) : _device(device), _pipelineData(pipelineData)
	{
	}

	DeviceDescriptorSimplifierInternal::~DeviceDescriptorSimplifierInternal()
	{
	}

	ListObjectID<AutoCleanupDescriptorPool> DeviceDescriptorSimplifierInternal::AddDescriptorPool(
		const std::vector<std::pair<PipelineLayoutDescriptorType, uint64_t>>& descriptorSetTypes, uint64_t maxTotalSets, bool freeIndividual)
	{
		if (maxTotalSets == 0)
			throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: Program tried to create a pool for maximum of zero total descriptor sets!");

		if (descriptorSetTypes.empty())
			throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: Program tried to create a pool for zero descriptor set types!");

		if (maxTotalSets > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: max total sets = " + std::to_string(maxTotalSets));

		if (descriptorSetTypes.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: erroneous descriptor set type list size = " + std::to_string(descriptorSetTypes.size()));

		VkDescriptorPool add = VK_NULL_HANDLE;

		VkDescriptorPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		createInfo.maxSets = static_cast<uint32_t>(maxTotalSets);

		if (freeIndividual)
			createInfo.flags |= VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

		std::vector<VkDescriptorPoolSize> descriptorTypeMaximums;
		descriptorTypeMaximums.reserve(descriptorSetTypes.size());
		
		for (size_t i = 0; i < descriptorSetTypes.size(); ++i)
		{
			auto& type = descriptorSetTypes[i];

			if (type.second > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: descriptor of a type " + GetPipelineLayoutDescriptorName(type.first) +
					std::string(", has erroneous max size = " + std::to_string(type.second)));

			auto descriptorType = Utils::TranslateDescriptorType(type.first);

			for (size_t j = 0; j < descriptorTypeMaximums.size(); ++j)
			{
				if (descriptorTypeMaximums[j].type == descriptorType)
					throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: Single type of descriptor has multiple entries in list. Detected indexes are " +
						std::to_string(j) + std::string(" and ") + std::to_string(i));
			}

			if (descriptorType == VK_DESCRIPTOR_TYPE_MAX_ENUM)
				throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: Program was given an erroneous descriptor type in index " + std::to_string(i));

			descriptorTypeMaximums.emplace_back(descriptorType, static_cast<uint32_t>(type.second));
		}

		createInfo.poolSizeCount = static_cast<uint32_t>(descriptorTypeMaximums.size());
		createInfo.pPoolSizes = descriptorTypeMaximums.data();

		if (vkCreateDescriptorPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceDescriptorSimplifierInternal::AddDescriptorPool Error: Program failed to create a descriptor pool!");

		return _descriptorPools.AddObject(AutoCleanupDescriptorPool(add, _device, static_cast<uint32_t>(maxTotalSets), freeIndividual, std::move(descriptorTypeMaximums)));
	}

	std::vector<ListObjectID<UniformBufferDescriptorSet>> DeviceDescriptorSimplifierInternal::AddUniformBuffers(ListObjectID<AutoCleanupDescriptorPool> poolID,
		const std::vector<ListObjectID<AutoCleanupDescriptorSetLayout>>& descriptorLayoutIDs)
	{
		auto& descriptorPool = _descriptorPools.GetObject(poolID);

		auto descriptorLayouts = _pipelineData.GetDescriptorSetLayouts(descriptorLayoutIDs);

		return descriptorPool.AddUniformBuffers(descriptorLayouts);
	}

	UniformBufferDescriptorSet::UniformBufferDescriptorSet(VkDescriptorSet descriptorSet) : BasicDescriptorSet(descriptorSet)
	{
	}

	UniformBufferDescriptorSet::~UniformBufferDescriptorSet()
	{
	}

}