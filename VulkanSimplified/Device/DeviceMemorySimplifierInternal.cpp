#include "../Other/pch.h"
#include "DeviceMemorySimplifierInternal.h"

namespace VulkanSimplified
{

	AutoCleanupMemory::AutoCleanupMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : _device(device), _mapping(nullptr), _deviceMemory(deviceMemory),
		_memorySize(memorySize)
	{
		_usedMemory.reserve(0x10);
	}

	AutoCleanupMemory::~AutoCleanupMemory()
	{
		if (_deviceMemory != VK_NULL_HANDLE)
		{
			vkUnmapMemory(_device, _deviceMemory);
			vkFreeMemory(_device, _deviceMemory, nullptr);
		}
	}

	AutoCleanupMemory::AutoCleanupMemory(AutoCleanupMemory&& other) noexcept : _device(other._device), _mapping(other._mapping), _deviceMemory(other._deviceMemory),
		_memorySize(other._memorySize), _usedMemory(std::move(other._usedMemory))
	{
		other._device = VK_NULL_HANDLE;
		other._mapping = nullptr;
		other._deviceMemory = VK_NULL_HANDLE;
		other._memorySize = 0;
	}

	AutoCleanupMemory& AutoCleanupMemory::operator=(AutoCleanupMemory&& other) noexcept
	{
		_device = other._device;
		_mapping = other._mapping;
		_deviceMemory = other._deviceMemory;
		_memorySize = other._memorySize;
		_usedMemory = std::move(other._usedMemory);

		other._device = VK_NULL_HANDLE;
		other._mapping = nullptr;
		other._deviceMemory = VK_NULL_HANDLE;
		other._memorySize = 0;

		return *this;
	}

	bool DeviceMemorySimplifierInternal::IsHeapInTheArray(uint32_t heapID, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const
	{
		for (size_t i = 0; i < VK_MAX_MEMORY_HEAPS; ++i)
		{
			if (array[i] >= VK_MAX_MEMORY_HEAPS)
				break;

			if (heapID == array[i])
				return true;
		}

		return false;
	}

	std::optional<size_t> DeviceMemorySimplifierInternal::GetFirstEmptySpace(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const
	{
		std::optional<size_t> ret;

		for (size_t i = 0; i < VK_MAX_MEMORY_HEAPS; ++i)
		{
			if (array[i] >= VK_MAX_MEMORY_HEAPS)
			{
				ret = i;
				break;
			}
		}

		return ret;
	}

	size_t DeviceMemorySimplifierInternal::GetArrayUsedSize(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const
	{
		size_t ret = 0x10;
		auto get = GetFirstEmptySpace(array);

		if (get.has_value())
			ret = get.value();

		return ret;
	}

	void DeviceMemorySimplifierInternal::AddHeapToArray(uint32_t heapID, std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array)
	{
		if (!IsHeapInTheArray(heapID, array))
		{
			auto position = GetFirstEmptySpace(array);

			if (position.has_value())
			{
				array[position.value()] = heapID;
			}
			else
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddHeapToArray Error: Program tried to add more heapIDs than maximum heap amount!");
		}
	}

	std::optional<size_t> DeviceMemorySimplifierInternal::PickHeapToAddMemoryTo(uint64_t neededSize, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const
	{
		std::optional<size_t> ret;

		if (neededSize == 0)
			throw std::runtime_error("DeviceMemorySimplifierInternal::PickHeapToAddMemoryTo Error: Program was given zero as the needed memory size!");

		std::pair<uint32_t, VkDeviceSize> bestHeap = { std::numeric_limits<uint32_t>::max(), neededSize - 1};

		for (size_t i = 0; i < GetArrayUsedSize(array); ++i)
		{
			std::pair<uint32_t, VkDeviceSize> currentHeap;
			currentHeap.first = array[i];
			currentHeap.second = _memoryProperties.memoryHeaps[array[i]].size - _usedheapMemory[array[i]];

			if (bestHeap.second < currentHeap.second)
			{
				bestHeap = currentHeap;
				ret = bestHeap.first;
			}
		}

		return ret;
	}

	std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentExternalMemory>> DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentExternalMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleCachedCoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _externalCachedCoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleCachedCoherentExternalMemories.AddObject(AutoCleanupAccesibleCachedCoherentExternalMemory(_device, add, memorySize));
		}

		return ret;
	}

	std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentExternalMemory>> DeviceMemorySimplifierInternal::AddCachedIncoherentExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentExternalMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleCachedIncoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _externalCachedIncoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleCachedIncoherentExternalMemories.AddObject(AutoCleanupAccesibleCachedIncoherentExternalMemory(_device, add, memorySize));
		}

		return ret;
	}

	void DeviceMemorySimplifierInternal::IncreaseUsedHeapMemory(uint64_t addedMemory, uint32_t heapID)
	{
		if (heapID >= VK_MAX_MEMORY_HEAPS)
			throw std::runtime_error("DeviceMemorySimplifierInternal::IncreaseUsedHeapMemory Error: Function was given an erroneous heap ID!");

		if (_usedheapMemory[heapID] + addedMemory < _usedheapMemory[heapID])
			throw std::runtime_error("DeviceMemorySimplifierInternal::IncreaseUsedHeapMemory Error: used heap memory overflow!");

		_usedheapMemory[heapID] += addedMemory;
	}

	std::optional<ListObjectID<AutoCleanupAccesibleUncachedExternalMemory>> DeviceMemorySimplifierInternal::AddUncachedExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleUncachedExternalMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleUncachedDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _externalUncachedMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleUncachedExternalMemories.AddObject(AutoCleanupAccesibleUncachedExternalMemory(_device, add, memorySize));
		}

		return ret;
	}

	void DeviceMemorySimplifierInternal::DecreaseUsedHeapMemory(uint64_t substractedMemory, uint32_t heapID)
	{
		if (heapID >= VK_MAX_MEMORY_HEAPS)
			throw std::runtime_error("DeviceMemorySimplifierInternal::DecreaseUsedHeapMemory Error: Function was given an erroneous heap ID!");

		if (_usedheapMemory[heapID] - substractedMemory > _usedheapMemory[heapID])
			throw std::runtime_error("DeviceMemorySimplifierInternal::DecreaseUsedHeapMemory Error: used heap memory underflow!");

		_usedheapMemory[heapID] -= substractedMemory;
	}

	std::optional<ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory>> DeviceMemorySimplifierInternal::AddCachedCoherentSharedMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _sharedCachedCoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _sharedCachedCoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedCachedCoherentDeviceMemories.AddObject(AutoCleanupSharedCachedCoherentDeviceMemory(_device, add, memorySize));
		}

		return ret;
	}

	uint32_t DeviceMemorySimplifierInternal::FindMemoryType(uint32_t heapID, VkMemoryPropertyFlags includeFlags)
	{
		uint32_t ret = _memoryProperties.memoryTypeCount;

		for (size_t i = 0; i < _memoryProperties.memoryTypeCount; ++i)
		{
			auto& memory = _memoryProperties.memoryTypes[i];
			if (memory.heapIndex != heapID)
				continue;

			if (memory.propertyFlags == includeFlags)
			{
				ret = i;
				break;
			}
		}

		if (ret >= _memoryProperties.memoryTypeCount)
			throw std::runtime_error("DeviceMemorySimplifierInternal::FindMemoryType Error: Program failed to find an appropriate memory type!");

		return ret;
	}

	std::optional<ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory>> DeviceMemorySimplifierInternal::AddCachedIncoherentSharedMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _sharedCachedIncoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _sharedCachedIncoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedCachedIncoherentDeviceMemories.AddObject(AutoCleanupSharedCachedIncoherentDeviceMemory(_device, add, memorySize));
		}

		return ret;
	}

	std::optional<ListObjectID<AutoCleanupSharedUncachedDeviceMemory>> DeviceMemorySimplifierInternal::AddUncachedSharedMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupSharedUncachedDeviceMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _sharedUnchachedDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _sharedUncachedMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedUncachedDeviceMemories.AddObject(AutoCleanupSharedUncachedDeviceMemory(_device, add, memorySize));
		}

		return ret;
	}

	DeviceMemorySimplifierInternal::DeviceMemorySimplifierInternal(VkPhysicalDevice physicalDevice, VkDevice device) : _physicalDevice(physicalDevice), _device(device),
		_memoryProperties()
	{
		vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &_memoryProperties);

		memset(_usedheapMemory, 0, sizeof(_usedheapMemory));

		memset(_sharedUnchachedDeviceHeaps.data(), 0xff, sizeof(_sharedUnchachedDeviceHeaps));
		memset(_sharedCachedCoherentDeviceHeaps.data(), 0xff, sizeof(_sharedCachedCoherentDeviceHeaps));
		memset(_sharedCachedIncoherentDeviceHeaps.data(), 0xff, sizeof(_sharedCachedIncoherentDeviceHeaps));
		memset(_exclusiveDeviceHeaps.data(), 0xff, sizeof(_exclusiveDeviceHeaps));
		memset(_accessibleCachedCoherentDeviceHeaps.data(), 0xff, sizeof(_accessibleCachedCoherentDeviceHeaps));
		memset(_accessibleCachedIncoherentDeviceHeaps.data(), 0xff, sizeof(_accessibleCachedIncoherentDeviceHeaps));
		memset(_accessibleUncachedDeviceHeaps.data(), 0xff, sizeof(_accessibleUncachedDeviceHeaps));

		_deviceLocalMemoryProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		_externalUncachedMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		_externalCachedCoherentMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		_externalCachedIncoherentMemoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		_sharedUncachedMemoryProperties = _deviceLocalMemoryProperties | _externalUncachedMemoryProperties;
		_sharedCachedCoherentMemoryProperties = _deviceLocalMemoryProperties | _externalCachedCoherentMemoryProperties;
		_sharedCachedIncoherentMemoryProperties = _deviceLocalMemoryProperties | _externalCachedIncoherentMemoryProperties;
		_flagsPadding = 0;

		auto& memoryInfo = _memoryProperties;
		for (uint32_t j = 0; j < memoryInfo.memoryTypeCount; ++j)
		{
			const VkMemoryHeap& heap = memoryInfo.memoryHeaps[memoryInfo.memoryTypes[j].heapIndex];
			const VkMemoryPropertyFlags& flags = memoryInfo.memoryTypes[j].propertyFlags;

			if ((heap.flags ^ VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == 0)
			{
				if (flags == _deviceLocalMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _exclusiveDeviceHeaps);
				}
				else if (flags == _sharedUncachedMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _sharedUnchachedDeviceHeaps);
				}
				else if (flags == _sharedCachedCoherentMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _sharedCachedCoherentDeviceHeaps);
				}
				else if (flags == _sharedCachedIncoherentMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _sharedCachedIncoherentDeviceHeaps);
				}
			}
			else if (heap.flags == 0)
			{
				if (flags == _externalUncachedMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _accessibleUncachedDeviceHeaps);
				}
				else if (flags == _externalCachedCoherentMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _accessibleCachedCoherentDeviceHeaps);
				}
				else if (flags == _externalCachedIncoherentMemoryProperties)
				{
					AddHeapToArray(memoryInfo.memoryTypes[j].heapIndex, _accessibleCachedIncoherentDeviceHeaps);
				}
			}
		}
	}

	std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> DeviceMemorySimplifierInternal::AddDeviceLocalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> ret;

		auto heap = PickHeapToAddMemoryTo(memorySize, _exclusiveDeviceHeaps);

		if (heap.has_value())
		{
			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.memoryTypeIndex = FindMemoryType(heap.value(), _deviceLocalMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) == VK_SUCCESS)
				ret = _exclusiveDeviceMemories.AddObject(AutoCleanupExclusiveDeviceMemory(_device, add, memorySize));
		}

		return ret;
	}

	SharedDeviceMemoryID DeviceMemorySimplifierInternal::AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		SharedDeviceMemoryID ret;

		auto cachedCoherent = AddCachedCoherentSharedMemory(memorySize);

		if (cachedCoherent.has_value())
		{
			ret._cachedCoherentID._type = MemoryPropertiesIDType::CACHED_COHERENT;
			ret._cachedCoherentID._ID = cachedCoherent.value();
		}
		else
		{
			if (canBeUncached)
			{
				auto uncached = AddUncachedSharedMemory(memorySize);

				if (uncached.has_value())
				{
					ret._unchachedID._type = MemoryPropertiesIDType::UNCACHED;
					ret._unchachedID._ID = uncached.value();
					return ret;
				}
			}

			if (canBeIncoherent)
			{
				auto incoherent = AddCachedIncoherentSharedMemory(memorySize);

				if (incoherent.has_value())
				{
					ret._cachedIncoherentID._type = MemoryPropertiesIDType::CACHED_INCOHERENT;
					ret._cachedIncoherentID._ID = incoherent.value();
				}
			}
		}

		return ret;
	}

	ExternalAccessibleMemoryID DeviceMemorySimplifierInternal::AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		ExternalAccessibleMemoryID ret;

		auto cachedCoherent = AddCachedCoherentExternalMemory(memorySize);

		if (cachedCoherent.has_value())
		{
			ret._cachedCoherentID._type = MemoryPropertiesIDType::CACHED_COHERENT;
			ret._cachedCoherentID._ID = cachedCoherent.value();
		}
		else
		{
			if (canBeUncached)
			{
				auto uncached = AddUncachedExternalMemory(memorySize);

				if (uncached.has_value())
				{
					ret._unchachedID._type = MemoryPropertiesIDType::UNCACHED;
					ret._unchachedID._ID = uncached.value();
					return ret;
				}
			}

			if (canBeIncoherent)
			{
				auto incoherent = AddCachedIncoherentExternalMemory(memorySize);

				if (incoherent.has_value())
				{
					ret._cachedIncoherentID._type = MemoryPropertiesIDType::CACHED_INCOHERENT;
					ret._cachedIncoherentID._ID = incoherent.value();
				}
			}
		}

		return ret;
	}

	AutoCleanupMappedMemory::AutoCleanupMappedMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMemory(device, deviceMemory, memorySize)
	{
		vkMapMemory(_device, _deviceMemory, 0, memorySize, 0, &_mapping);
	}

}