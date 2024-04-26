#include "../Other/pch.h"
#include "DeviceMemorySimplifierInternal.h"

namespace VulkanSimplified
{

	std::optional<std::pair<VkDeviceSize, size_t>> AutoCleanupMemory::GetMemoryOffset(VkMemoryRequirements suballocationRequirements)
	{
		std::optional<std::pair<VkDeviceSize, size_t>> ret;

		if (suballocationRequirements.size > _memorySize)
			throw std::runtime_error("AutoCleanupMemory::GetSubmemoryBeggining Error: Program tried to suballocate more memory than is available in entire allocation!");

		size_t listSize = _usedMemory.GetListSize();

		if (listSize == 0)
		{
			ret = { 0, 0 };
		}
		else
		{
			size_t allocPos = _usedMemory.GetFirstUndeleted();
			VkDeviceSize previousObjectsEnd = 0;

			while (allocPos != listSize)
			{
				auto& currentObj = _usedMemory.GetConstObjectFromPosition(allocPos);

				if (currentObj._memoryOffset > previousObjectsEnd)
				{
					VkDeviceSize gapSize = currentObj._memoryOffset - previousObjectsEnd;

					if (gapSize >= suballocationRequirements.size)
					{
						ret = { previousObjectsEnd, allocPos };
						break;
					}
				}

				allocPos = _usedMemory.GetNextUndeleted(allocPos);
				previousObjectsEnd = currentObj._memoryOffset + currentObj._objectSize;

				VkDeviceSize aligmentGap = previousObjectsEnd % suballocationRequirements.alignment;

				if (aligmentGap != 0)
					previousObjectsEnd += suballocationRequirements.alignment - aligmentGap;
			}

			if (allocPos == listSize)
			{
				auto& lastPos = _usedMemory.GetConstObjectFromPosition(allocPos - 1);

				VkDeviceSize lastObjectsEnd = lastPos._memoryOffset + lastPos._objectSize;

				VkDeviceSize aligmentGap = lastObjectsEnd % suballocationRequirements.alignment;

				if (aligmentGap != 0)
					lastObjectsEnd += suballocationRequirements.alignment - aligmentGap;

				if (lastObjectsEnd <= _memorySize)
				{
					VkDeviceSize memoryLeft = _memorySize - lastObjectsEnd;

					if (memoryLeft >= suballocationRequirements.size)
					{
						ret = { lastObjectsEnd, allocPos };
					}
				}
			}
		}

		return ret;
	}

	AutoCleanupMemory::AutoCleanupMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : _device(device), _mapping(nullptr),
		_memoryIndex(memoryIndex), _deviceMemory(deviceMemory), _memorySize(memorySize)
	{
	}

	AutoCleanupMemory::~AutoCleanupMemory()
	{
		if (_deviceMemory != VK_NULL_HANDLE)
		{
			vkUnmapMemory(_device, _deviceMemory);
			vkFreeMemory(_device, _deviceMemory, nullptr);
		}
	}

	AutoCleanupMemory::AutoCleanupMemory(AutoCleanupMemory&& other) noexcept : _device(other._device), _mapping(other._mapping), _memoryIndex(other._memoryIndex),
		_deviceMemory(other._deviceMemory), _memorySize(other._memorySize), _usedMemory(std::move(other._usedMemory))
	{
		other._device = VK_NULL_HANDLE;
		other._mapping = nullptr;
		other._memoryIndex = std::numeric_limits<uint64_t>::max();
		other._deviceMemory = VK_NULL_HANDLE;
		other._memorySize = 0;
	}

	AutoCleanupMemory& AutoCleanupMemory::operator=(AutoCleanupMemory&& other) noexcept
	{
		_device = other._device;
		_mapping = other._mapping;
		_memoryIndex = other._memoryIndex;
		_deviceMemory = other._deviceMemory;
		_memorySize = other._memorySize;
		_usedMemory = std::move(other._usedMemory);

		other._device = VK_NULL_HANDLE;
		other._mapping = nullptr;
		other._memoryIndex = std::numeric_limits<uint64_t>::max();
		other._deviceMemory = VK_NULL_HANDLE;
		other._memorySize = 0;

		return *this;
	}

	std::optional<ListObjectID<MemoryObject>> AutoCleanupMemory::SuballocateMemory(VkMemoryRequirements suballocationRequirements, size_t add)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto position = GetMemoryOffset(suballocationRequirements);

		if (position.has_value())
		{
			ret = _usedMemory.AddObjectBeforePosition({ position.value().first, suballocationRequirements.size }, position.value().second, add);
		}

		return ret;
	}

	void AutoCleanupMemory::BindBuffer(ListObjectID<MemoryObject> bufferSuballocation, VkBuffer buffer)
	{
		auto& subMemory = _usedMemory.GetConstObject(bufferSuballocation);

		if (vkBindBufferMemory(_device, buffer, _deviceMemory, subMemory._memoryOffset) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanupMemory::BindBuffer Error: Program failed to bind buffer to the suballocated memory!");
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

	std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory>> DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleCachedCoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _externalCachedCoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleCachedCoherentExternalMemories.AddObject(AutoCleanupAccesibleCachedCoherentHostMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
		}

		return ret;
	}

	std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory>> DeviceMemorySimplifierInternal::AddCachedIncoherentExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleCachedIncoherentDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _externalCachedIncoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleCachedIncoherentExternalMemories.AddObject(AutoCleanupAccesibleCachedIncoherentHostMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
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

	std::optional<ListObjectID<AutoCleanupAccesibleUncachedHostMemory>> DeviceMemorySimplifierInternal::AddUncachedExternalMemory(uint64_t memorySize)
	{
		std::optional<ListObjectID<AutoCleanupAccesibleUncachedHostMemory>> ret;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		auto heap = PickHeapToAddMemoryTo(memorySize, _accessibleUncachedDeviceHeaps);

		if (heap.has_value())
		{
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _externalUncachedMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _accessibleUncachedExternalMemories.AddObject(AutoCleanupAccesibleUncachedHostMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
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
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _sharedCachedCoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedCachedCoherentDeviceMemories.AddObject(AutoCleanupSharedCachedCoherentDeviceMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
		}

		return ret;
	}

	uint32_t DeviceMemorySimplifierInternal::FindMemoryType(uint32_t heapID, VkMemoryPropertyFlags includeFlags)
	{
		uint32_t ret = _memoryProperties.memoryTypeCount;

		for (uint32_t i = 0; i < _memoryProperties.memoryTypeCount; ++i)
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
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _sharedCachedIncoherentMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedCachedIncoherentDeviceMemories.AddObject(AutoCleanupSharedCachedIncoherentDeviceMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
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
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _sharedUncachedMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) != VK_SUCCESS)
				throw std::runtime_error("DeviceMemorySimplifierInternal::AddCachedCoherentExternalMemory Error: Program failed to allocate the memory!");

			ret = _sharedUncachedDeviceMemories.AddObject(AutoCleanupSharedUncachedDeviceMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
		}

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::BindBufferToMemory(AutoCleanupMemory& memory, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret = memory.SuballocateMemory(memReq, addOnReserve);

		if (ret.has_value())
		{
			memory.BindBuffer(ret.value(), buffer);
		}

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _sharedCachedCoherentDeviceMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _sharedCachedIncoherentDeviceMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _sharedUncachedDeviceMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToSharedMemory(SharedDeviceMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		switch (memoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			ret = TryToBindBufferToSharedUncachedMemory(memoryID._unchachedID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			ret = TryToBindBufferToSharedCachedIncoherentMemory(memoryID._cachedIncoherentID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			ret = TryToBindBufferToSharedCachedCoherentMemory(memoryID._cachedCoherentID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::TryToBindBufferToSharedMemory Error: Program was given an erroneous memory settings value!");
		}

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToExclusiveMemory(ListObjectID<AutoCleanupExclusiveDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _exclusiveDeviceMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	void DeviceMemorySimplifierInternal::WriteToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize)
	{
		auto& memory = _sharedCachedCoherentDeviceMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);
	}

	void DeviceMemorySimplifierInternal::WriteToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		auto& memory = _sharedCachedIncoherentDeviceMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);

		if (flushOnWrite)
			memory.FlushMemory({ objectID });
	}

	void DeviceMemorySimplifierInternal::WriteToSharedSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize)
	{
		auto& memory = _sharedUncachedDeviceMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);
	}

	void DeviceMemorySimplifierInternal::WriteToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize)
	{
		auto& memory = _accessibleCachedCoherentExternalMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);
	}

	void DeviceMemorySimplifierInternal::WriteToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		auto& memory = _accessibleCachedIncoherentExternalMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);

		if (flushOnWrite)
			memory.FlushMemory({ objectID });
	}

	void DeviceMemorySimplifierInternal::WriteToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, ListObjectID<MemoryObject> objectID,
		VkDeviceSize offset, const char& data, VkDeviceSize dataSize)
	{
		auto& memory = _accessibleUncachedExternalMemories.GetObject(memoryID);

		memory.WriteToMemoryObject(objectID, offset, data, dataSize);
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
			allocInfo.memoryTypeIndex = FindMemoryType(static_cast<uint32_t>(heap.value()), _deviceLocalMemoryProperties);
			allocInfo.allocationSize = memorySize;

			VkDeviceMemory add = VK_NULL_HANDLE;
			if (vkAllocateMemory(_device, &allocInfo, nullptr, &add) == VK_SUCCESS)
				ret = _exclusiveDeviceMemories.AddObject(AutoCleanupExclusiveDeviceMemory(_device, allocInfo.memoryTypeIndex, add, memorySize));
		}

		return ret;
	}

	SharedDeviceMemoryID DeviceMemorySimplifierInternal::AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		SharedDeviceMemoryID ret;

		auto cachedCoherent = AddCachedCoherentSharedMemory(memorySize);

		if (cachedCoherent.has_value())
		{
			ret._cachedCoherentID.type = MemoryPropertiesIDType::CACHED_COHERENT;
			ret._cachedCoherentID.ID = cachedCoherent.value();
		}
		else
		{
			if (canBeUncached)
			{
				auto uncached = AddUncachedSharedMemory(memorySize);

				if (uncached.has_value())
				{
					ret._unchachedID.type = MemoryPropertiesIDType::UNCACHED;
					ret._unchachedID.ID = uncached.value();
					return ret;
				}
			}

			if (canBeIncoherent)
			{
				auto incoherent = AddCachedIncoherentSharedMemory(memorySize);

				if (incoherent.has_value())
				{
					ret._cachedIncoherentID.type = MemoryPropertiesIDType::CACHED_INCOHERENT;
					ret._cachedIncoherentID.ID = incoherent.value();
				}
			}
		}

		return ret;
	}

	AccessibleHostMemoryID DeviceMemorySimplifierInternal::AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		AccessibleHostMemoryID ret;

		auto cachedCoherent = AddCachedCoherentExternalMemory(memorySize);

		if (cachedCoherent.has_value())
		{
			ret._cachedCoherentID.type = MemoryPropertiesIDType::CACHED_COHERENT;
			ret._cachedCoherentID.ID = cachedCoherent.value();
		}
		else
		{
			if (canBeUncached)
			{
				auto uncached = AddUncachedExternalMemory(memorySize);

				if (uncached.has_value())
				{
					ret._unchachedID.type = MemoryPropertiesIDType::UNCACHED;
					ret._unchachedID.ID = uncached.value();
					return ret;
				}
			}

			if (canBeIncoherent)
			{
				auto incoherent = AddCachedIncoherentExternalMemory(memorySize);

				if (incoherent.has_value())
				{
					ret._cachedIncoherentID.type = MemoryPropertiesIDType::CACHED_INCOHERENT;
					ret._cachedIncoherentID.ID = incoherent.value();
				}
			}
		}

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBuffer(MemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		switch (memoryID.memoryType)
		{
		case MemoryType::EXCLUSIVE:
			ret = BindBufferToExclusiveMemory(memoryID._exclusiveID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryType::HOST:
			ret = BindBufferToHostMemory(memoryID._hostID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryType::SHARED:
			ret = BindBufferToSharedMemory(memoryID._sharedID.ID, buffer, memReq, addOnReserve);
			break;
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBuffer Error: Program was given an erroneous memory ID type value!");
		}

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBuffer(MemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		switch (memoryID.memoryType)
		{
		case MemoryType::EXCLUSIVE:
			ret = TryToBindBufferToExclusiveMemory(memoryID._exclusiveID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryType::HOST:
			ret = TryToBindBufferToHostMemory(memoryID._hostID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryType::SHARED:
			ret = TryToBindBufferToSharedMemory(memoryID._sharedID.ID, buffer, memReq, addOnReserve);
			break;
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::TryToBindBuffer Error: Program was given an erroneous memory ID type value!");
		}

		return ret;
	}

	void DeviceMemorySimplifierInternal::WriteToMemoryObject(MemoryID memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		switch (memoryID.memoryType)
		{
		case MemoryType::EXCLUSIVE:
			throw std::runtime_error("DeviceMemorySimplifierInternal::WriteToMemoryObject Error: Program tried to write data to the gpu's exclusive access memory!");
		case MemoryType::HOST:
			WriteToMemoryObject(memoryID._hostID.ID, objectID, offset, data, dataSize, flushOnWrite);
			break;
		case MemoryType::SHARED:
			WriteToMemoryObject(memoryID._sharedID.ID, objectID, offset, data, dataSize, flushOnWrite);
			break;
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::WriteToMemoryObject Error: Program was given an erroneous memory ID type value!");
		}
	}

	void DeviceMemorySimplifierInternal::WriteToMemoryObject(SharedDeviceMemoryID sharedMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
		const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		switch (sharedMemoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			WriteToSharedSharedUncachedMemory(sharedMemoryID._unchachedID.ID, objectID, offset, data, dataSize);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			WriteToSharedCachedIncoherentMemory(sharedMemoryID._cachedIncoherentID.ID, objectID, offset, data, dataSize, flushOnWrite);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			WriteToSharedCachedCoherentMemory(sharedMemoryID._cachedCoherentID.ID, objectID, offset, data, dataSize);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::WriteToMemoryObject Error: Program was given an erroneous shared memory id!");
		}
	}

	void DeviceMemorySimplifierInternal::WriteToMemoryObject(AccessibleHostMemoryID hostMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
		const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		switch (hostMemoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			WriteToHostUncachedMemory(hostMemoryID._unchachedID.ID, objectID, offset, data, dataSize);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			WriteToHostCachedIncoherentMemory(hostMemoryID._cachedIncoherentID.ID, objectID, offset, data, dataSize, flushOnWrite);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			WriteToHostCachedCoherentMemory(hostMemoryID._cachedCoherentID.ID, objectID, offset, data, dataSize);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::WriteToMemoryObject Error: Program was given an erroneous host memory id!");
		}
	}

	AutoCleanupMappedMemory::AutoCleanupMappedMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
		AutoCleanupMemory(device, memoryIndex, deviceMemory, memorySize)
	{
		vkMapMemory(_device, _deviceMemory, 0, memorySize, 0, &_mapping);
	}

	void AutoCleanupMappedMemory::WriteToMemoryObject(ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize)
	{
		if (dataSize > _memorySize)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Program tried to write to memory a data stream bigger than the entire memory!");

		if (offset >= _memorySize)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Program tried to write to memory at a position past the memory's end!");

		auto& object = _usedMemory.GetConstObject(objectID);

		if (dataSize > object._objectSize)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Program tried to write to memory object a data stream bigger than the object entire memory!");

		if (offset >= object._objectSize)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Program tried to write to memory object at position past the objects end!");

		VkDeviceSize sizeLeft = object._objectSize - offset;

		if (dataSize > sizeLeft)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Program tried to write to memory object a data stream bigger than the object memory after offset!");

		VkDeviceSize totaloffset = object._memoryOffset + offset;

		if (totaloffset < offset)
			throw std::runtime_error("AutoCleanupMappedMemory::WriteToMemoryObject Error: Total offset overflowed!");

		memcpy(static_cast<char*>(_mapping) + totaloffset, &data, static_cast<size_t>(dataSize));
	}

	void AutoCleanupMappedMemory::FlushMemory(const std::vector<ListObjectID<MemoryObject>>& objectIDs)
	{
		if (objectIDs.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("AutoCleanupMappedMemory::FlushMemory Error: Object IDs vector overflow!");

		std::vector<VkMappedMemoryRange> _memoryRanges;
		_memoryRanges.reserve(objectIDs.size());

		for (auto& objectID : objectIDs)
		{
			auto& object = _usedMemory.GetConstObject(objectID);

			VkMappedMemoryRange add{};
			add.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			add.memory = _deviceMemory;
			add.offset = object._memoryOffset;
			add.size = object._objectSize;

			_memoryRanges.push_back(add);
		}

		if (vkFlushMappedMemoryRanges(_device, static_cast<uint32_t>(_memoryRanges.size()), _memoryRanges.data()) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanupMappedMemory::FlushMemory Error: Program failed to flush the memory ranges!");
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _accessibleCachedCoherentExternalMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToHostCachedCoherentMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _accessibleCachedIncoherentExternalMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToHostCachedIncoherentMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _accessibleUncachedExternalMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToHostUncachedMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToHostMemory(AccessibleHostMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements req, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		switch (memoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			ret = BindBufferToHostUncachedMemory(memoryID._unchachedID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			ret = BindBufferToHostCachedIncoherentMemory(memoryID._cachedIncoherentID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			ret = BindBufferToHostCachedCoherentMemory(memoryID._cachedCoherentID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToHostMemory Error: Program was given an erroneous memory settings value!");
		}

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _sharedCachedCoherentDeviceMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToSharedCachedCoherentMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _sharedCachedIncoherentDeviceMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToSharedCachedIncoherentMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _sharedUncachedDeviceMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToSharedUncachedMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToSharedMemory(SharedDeviceMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		switch (memoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			ret = BindBufferToSharedUncachedMemory(memoryID._unchachedID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			ret = BindBufferToSharedCachedIncoherentMemory(memoryID._cachedIncoherentID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			ret = BindBufferToSharedCachedCoherentMemory(memoryID._cachedCoherentID.ID, buffer, memReq, addOnReserve);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToSharedMemory Error: Program was given an erroneous memory settings value!");
		}

		return ret;
	}

	ListObjectID<MemoryObject> DeviceMemorySimplifierInternal::BindBufferToExclusiveMemory(ListObjectID<AutoCleanupExclusiveDeviceMemory> memoryID, VkBuffer buffer,
		VkMemoryRequirements memReq, size_t addOnReserve)
	{
		ListObjectID<MemoryObject> ret;

		auto& memory = _exclusiveDeviceMemories.GetObject(memoryID);

		auto bindingPoint = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		if (bindingPoint.has_value())
		{
			ret = bindingPoint.value();
		}
		else
			throw std::runtime_error("DeviceMemorySimplifierInternal::BindBufferToExclusiveMemory Error: Program failed to suballocate required memory!");

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _accessibleCachedCoherentExternalMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _accessibleCachedIncoherentExternalMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		auto& memory = _accessibleUncachedExternalMemories.GetObject(memoryID);

		ret = BindBufferToMemory(memory, buffer, memReq, addOnReserve);

		return ret;
	}

	std::optional<ListObjectID<MemoryObject>> DeviceMemorySimplifierInternal::TryToBindBufferToHostMemory(AccessibleHostMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements req, size_t addOnReserve)
	{
		std::optional<ListObjectID<MemoryObject>> ret;

		switch (memoryID.type)
		{
		case MemoryPropertiesIDType::UNCACHED:
			ret = TryToBindBufferToHostUncachedMemory(memoryID._unchachedID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_INCOHERENT:
			ret = TryToBindBufferToHostCachedIncoherentMemory(memoryID._cachedIncoherentID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::CACHED_COHERENT:
			ret = TryToBindBufferToHostCachedCoherentMemory(memoryID._cachedCoherentID.ID, buffer, req, addOnReserve);
			break;
		case MemoryPropertiesIDType::NONE:
		default:
			throw std::runtime_error("DeviceMemorySimplifierInternal::TryToBindBufferToHostMemory Error: Program was given an erroneous memory settings value!");
		}

		return ret;
	}

}