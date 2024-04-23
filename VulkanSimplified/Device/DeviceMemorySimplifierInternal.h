#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Other/SortedListTemplate.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	struct MemoryObject
	{
		VkDeviceSize _memoryOffset = std::numeric_limits<VkDeviceSize>::max();
		VkDeviceSize _objectSize = 0;
	};

	class AutoCleanupMemory
	{
	protected:
		VkDevice _device;
		void* _mapping;
		uint64_t _memoryIndex;
		VkDeviceMemory _deviceMemory;
		VkDeviceSize _memorySize;
		SortedListTemplate<MemoryObject> _usedMemory;

		std::optional<std::pair<VkDeviceSize, size_t>> GetMemoryOffset(VkMemoryRequirements suballocationRequirements);

	public:
		AutoCleanupMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize);
		~AutoCleanupMemory();

		AutoCleanupMemory(const AutoCleanupMemory&) noexcept = delete;
		AutoCleanupMemory(AutoCleanupMemory&& other) noexcept;

		AutoCleanupMemory& operator=(const AutoCleanupMemory&) noexcept = delete;
		AutoCleanupMemory& operator=(AutoCleanupMemory&& other) noexcept;

		std::optional<ListObjectID<MemoryObject>> SuballocateMemory(VkMemoryRequirements suballocationRequirements, size_t add);

		void BindBuffer(ListObjectID<MemoryObject> bufferSuballocation, VkBuffer buffer);
	};

	class AutoCleanupMappedMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupMappedMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize);
		~AutoCleanupMappedMemory() {}

		AutoCleanupMappedMemory(const AutoCleanupMappedMemory&) noexcept = delete;
		AutoCleanupMappedMemory(AutoCleanupMappedMemory&& other) noexcept : AutoCleanupMemory(std::move(other))
		{
		}

		AutoCleanupMappedMemory& operator=(const AutoCleanupMappedMemory&) noexcept = delete;
		AutoCleanupMappedMemory& operator=(AutoCleanupMappedMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}

		void WriteToMemoryObject(ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize);
		void FlushMemory(const std::vector<ListObjectID<MemoryObject>>& objectIDs);
	};

	class AutoCleanupSharedUncachedDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedUncachedDeviceMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupSharedUncachedDeviceMemory() {}

		AutoCleanupSharedUncachedDeviceMemory(const AutoCleanupSharedUncachedDeviceMemory&) noexcept = delete;
		AutoCleanupSharedUncachedDeviceMemory(AutoCleanupSharedUncachedDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedUncachedDeviceMemory& operator=(const AutoCleanupSharedUncachedDeviceMemory&) noexcept = delete;
		AutoCleanupSharedUncachedDeviceMemory& operator=(AutoCleanupSharedUncachedDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupSharedCachedCoherentDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedCachedCoherentDeviceMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupSharedCachedCoherentDeviceMemory() {}

		AutoCleanupSharedCachedCoherentDeviceMemory(const AutoCleanupSharedCachedCoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedCoherentDeviceMemory(AutoCleanupSharedCachedCoherentDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedCachedCoherentDeviceMemory& operator=(const AutoCleanupSharedCachedCoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedCoherentDeviceMemory& operator=(AutoCleanupSharedCachedCoherentDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupSharedCachedIncoherentDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedCachedIncoherentDeviceMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupSharedCachedIncoherentDeviceMemory() {}

		AutoCleanupSharedCachedIncoherentDeviceMemory(const AutoCleanupSharedCachedIncoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedIncoherentDeviceMemory(AutoCleanupSharedCachedIncoherentDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedCachedIncoherentDeviceMemory& operator=(const AutoCleanupSharedCachedIncoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedIncoherentDeviceMemory& operator=(AutoCleanupSharedCachedIncoherentDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupExclusiveDeviceMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupExclusiveDeviceMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupExclusiveDeviceMemory() {}

		AutoCleanupExclusiveDeviceMemory(const AutoCleanupExclusiveDeviceMemory&) noexcept = delete;
		AutoCleanupExclusiveDeviceMemory(AutoCleanupExclusiveDeviceMemory&& other) noexcept : AutoCleanupMemory(std::move(other))
		{
		}

		AutoCleanupExclusiveDeviceMemory& operator=(const AutoCleanupExclusiveDeviceMemory&) noexcept = delete;
		AutoCleanupExclusiveDeviceMemory& operator=(AutoCleanupExclusiveDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleCachedCoherentHostMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupAccesibleCachedCoherentHostMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleCachedCoherentHostMemory() {}

		AutoCleanupAccesibleCachedCoherentHostMemory(const AutoCleanupAccesibleCachedCoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedCoherentHostMemory(AutoCleanupAccesibleCachedCoherentHostMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other)) {}

		AutoCleanupAccesibleCachedCoherentHostMemory& operator=(const AutoCleanupAccesibleCachedCoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedCoherentHostMemory& operator=(AutoCleanupAccesibleCachedCoherentHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleCachedIncoherentHostMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupAccesibleCachedIncoherentHostMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleCachedIncoherentHostMemory() {}

		AutoCleanupAccesibleCachedIncoherentHostMemory(const AutoCleanupAccesibleCachedIncoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedIncoherentHostMemory(AutoCleanupAccesibleCachedIncoherentHostMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other)) {}

		AutoCleanupAccesibleCachedIncoherentHostMemory& operator=(const AutoCleanupAccesibleCachedIncoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedIncoherentHostMemory& operator=(AutoCleanupAccesibleCachedIncoherentHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleUncachedHostMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupAccesibleUncachedHostMemory(VkDevice device, uint64_t memoryIndex, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) :
			AutoCleanupMappedMemory(device, memoryIndex, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleUncachedHostMemory() {}

		AutoCleanupAccesibleUncachedHostMemory(const AutoCleanupAccesibleUncachedHostMemory&) noexcept = delete;
		AutoCleanupAccesibleUncachedHostMemory(AutoCleanupAccesibleUncachedHostMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other)) {}

		AutoCleanupAccesibleUncachedHostMemory& operator=(const AutoCleanupAccesibleUncachedHostMemory&) noexcept = delete;
		AutoCleanupAccesibleUncachedHostMemory& operator=(AutoCleanupAccesibleUncachedHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class DeviceMemorySimplifierInternal
	{
		ListTemplate<AutoCleanupSharedUncachedDeviceMemory> _sharedUncachedDeviceMemories;
		ListTemplate<AutoCleanupSharedCachedCoherentDeviceMemory> _sharedCachedCoherentDeviceMemories;
		ListTemplate<AutoCleanupSharedCachedIncoherentDeviceMemory> _sharedCachedIncoherentDeviceMemories;
		ListTemplate<AutoCleanupExclusiveDeviceMemory> _exclusiveDeviceMemories;
		ListTemplate<AutoCleanupAccesibleCachedCoherentHostMemory> _accessibleCachedCoherentExternalMemories;
		ListTemplate<AutoCleanupAccesibleCachedIncoherentHostMemory> _accessibleCachedIncoherentExternalMemories;
		ListTemplate<AutoCleanupAccesibleUncachedHostMemory> _accessibleUncachedExternalMemories;

		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		VkPhysicalDeviceMemoryProperties _memoryProperties;
		VkDeviceSize _usedheapMemory[VK_MAX_MEMORY_HEAPS];

		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedUnchachedDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedCachedCoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedCachedIncoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _exclusiveDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleCachedCoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleCachedIncoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleUncachedDeviceHeaps;

		VkMemoryPropertyFlags _deviceLocalMemoryProperties;
		VkMemoryPropertyFlags _externalUncachedMemoryProperties;
		VkMemoryPropertyFlags _externalCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags _externalCachedIncoherentMemoryProperties;
		VkMemoryPropertyFlags _sharedUncachedMemoryProperties;
		VkMemoryPropertyFlags _sharedCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags _sharedCachedIncoherentMemoryProperties;
		VkMemoryPropertyFlags _flagsPadding;

		bool IsHeapInTheArray(uint32_t heapID, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;
		std::optional<size_t> GetFirstEmptySpace(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		size_t GetArrayUsedSize(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		void AddHeapToArray(uint32_t heapID, std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array);

		std::optional<size_t> PickHeapToAddMemoryTo(uint64_t neededSize, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		void IncreaseUsedHeapMemory(uint64_t addedMemory, uint32_t heapID);
		void DecreaseUsedHeapMemory(uint64_t substractedMemory, uint32_t heapID);

		uint32_t FindMemoryType(uint32_t heapID, VkMemoryPropertyFlags includeFlags);

		std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory>> AddCachedCoherentExternalMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory>> AddCachedIncoherentExternalMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupAccesibleUncachedHostMemory>> AddUncachedExternalMemory(uint64_t memorySize);

		std::optional<ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory>> AddCachedCoherentSharedMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory>> AddCachedIncoherentSharedMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupSharedUncachedDeviceMemory>> AddUncachedSharedMemory(uint64_t memorySize);

		std::optional<ListObjectID<MemoryObject>> BindBufferToMemory(AutoCleanupMemory& memory, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		ListObjectID<MemoryObject> BindBufferToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq,
			size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToHostMemory(AccessibleHostMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements req, size_t addOnReserve);

		ListObjectID<MemoryObject> BindBufferToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		ListObjectID<MemoryObject> BindBufferToSharedMemory(SharedDeviceMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		ListObjectID<MemoryObject> BindBufferToExclusiveMemory(ListObjectID<AutoCleanupExclusiveDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq,
			size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToHostMemory(AccessibleHostMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements req, size_t addOnReserve);

		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, VkBuffer buffer,
			VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToSharedMemory(SharedDeviceMemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		std::optional<ListObjectID<MemoryObject>> TryToBindBufferToExclusiveMemory(ListObjectID<AutoCleanupExclusiveDeviceMemory> memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		void WriteToSharedCachedCoherentMemory(ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize);
		void WriteToSharedCachedIncoherentMemory(ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize, bool flushOnWrite);
		void WriteToSharedSharedUncachedMemory(ListObjectID<AutoCleanupSharedUncachedDeviceMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize);

		void WriteToHostCachedCoherentMemory(ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize);
		void WriteToHostCachedIncoherentMemory(ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize, bool flushOnWrite);
		void WriteToHostUncachedMemory(ListObjectID<AutoCleanupAccesibleUncachedHostMemory> memoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset,
			const char& data, VkDeviceSize dataSize);

	public:
		DeviceMemorySimplifierInternal(VkPhysicalDevice physicalDevice, VkDevice device);

		DeviceMemorySimplifierInternal(const DeviceMemorySimplifierInternal&) noexcept = delete;
		DeviceMemorySimplifierInternal(DeviceMemorySimplifierInternal&&) noexcept = delete;

		DeviceMemorySimplifierInternal& operator=(const DeviceMemorySimplifierInternal&) noexcept = delete;
		DeviceMemorySimplifierInternal& operator=(DeviceMemorySimplifierInternal&&) noexcept = delete;

		std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> AddDeviceLocalMemory(uint64_t memorySize);
		SharedDeviceMemoryID AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
		AccessibleHostMemoryID AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);

		ListObjectID<MemoryObject> BindBuffer(MemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindBuffer(MemoryID memoryID, VkBuffer buffer, VkMemoryRequirements memReq, size_t addOnReserve);

		void WriteToMemoryObject(SharedDeviceMemoryID sharedMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite);
		void WriteToMemoryObject(AccessibleHostMemoryID hostMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite);
	};
}