#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	struct MemoryObject;
	class DeviceMemorySimplifierInternal;

	class AutoCleanupDataBuffer
	{
	protected:
		VkDevice _device;
		void* _ppadding;
		VkBuffer _dataBuffer;
		VkMemoryRequirements _memReq;
		std::optional<std::pair<MemoryID, ListObjectID<MemoryObject>>> _boundID;

	public:
		AutoCleanupDataBuffer(VkDevice device, VkBuffer dataBuffer);
		~AutoCleanupDataBuffer();

		AutoCleanupDataBuffer(const AutoCleanupDataBuffer&) noexcept = delete;
		AutoCleanupDataBuffer(AutoCleanupDataBuffer&& other) noexcept;

		AutoCleanupDataBuffer& operator=(const AutoCleanupDataBuffer&) noexcept = delete;
		AutoCleanupDataBuffer& operator=(AutoCleanupDataBuffer&& other) noexcept;

		VkBuffer GetBuffer() const;
		VkMemoryRequirements GetRequirements() const;

		std::optional<std::pair<MemoryID, ListObjectID<MemoryObject>>> GetBuffersBindingID() const;
		bool IsBufferBound() const;

		void BindBuffer(DeviceMemorySimplifierInternal& memoryData, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindBuffer(DeviceMemorySimplifierInternal& memoryData, MemoryID memoryID, size_t addOnReserve);
	};

	class AutoCleanupShaderInputBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupShaderInputBuffer(VkDevice device, VkBuffer dataBuffer) : AutoCleanupDataBuffer(device, dataBuffer) {}
		~AutoCleanupShaderInputBuffer() {}

		AutoCleanupShaderInputBuffer(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer(AutoCleanupShaderInputBuffer&& other) noexcept : AutoCleanupDataBuffer(std::move(other)) {}

		AutoCleanupShaderInputBuffer& operator=(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer& operator=(AutoCleanupShaderInputBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	class AutoCleanupStagingBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupStagingBuffer(VkDevice device, VkBuffer dataBuffer) : AutoCleanupDataBuffer(device, dataBuffer) {}
		~AutoCleanupStagingBuffer() {}

		AutoCleanupStagingBuffer(const AutoCleanupStagingBuffer&) noexcept = delete;
		AutoCleanupStagingBuffer(AutoCleanupStagingBuffer&& other) noexcept : AutoCleanupDataBuffer(std::move(other)) {}

		AutoCleanupStagingBuffer& operator=(const AutoCleanupStagingBuffer&) noexcept = delete;
		AutoCleanupStagingBuffer& operator=(AutoCleanupStagingBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	class AutoCleanupSmallIndexBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupSmallIndexBuffer(VkDevice device, VkBuffer dataBuffer) : AutoCleanupDataBuffer(device, dataBuffer) {}
		~AutoCleanupSmallIndexBuffer() {}

		AutoCleanupSmallIndexBuffer(const AutoCleanupSmallIndexBuffer&) noexcept = delete;
		AutoCleanupSmallIndexBuffer(AutoCleanupSmallIndexBuffer&& other) noexcept : AutoCleanupDataBuffer(std::move(other)) {}

		AutoCleanupSmallIndexBuffer& operator=(const AutoCleanupSmallIndexBuffer&) noexcept = delete;
		AutoCleanupSmallIndexBuffer& operator=(AutoCleanupSmallIndexBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	class AutoCleanupBigIndexBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupBigIndexBuffer(VkDevice device, VkBuffer dataBuffer) : AutoCleanupDataBuffer(device, dataBuffer) {}
		~AutoCleanupBigIndexBuffer() {}

		AutoCleanupBigIndexBuffer(const AutoCleanupBigIndexBuffer&) noexcept = delete;
		AutoCleanupBigIndexBuffer(AutoCleanupBigIndexBuffer&& other) noexcept : AutoCleanupDataBuffer(std::move(other)) {}

		AutoCleanupBigIndexBuffer& operator=(const AutoCleanupBigIndexBuffer&) noexcept = delete;
		AutoCleanupBigIndexBuffer& operator=(AutoCleanupBigIndexBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	class AutoCleanupDescriptorSetsBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupDescriptorSetsBuffer(VkDevice device, VkBuffer dataBuffer) : AutoCleanupDataBuffer(device, dataBuffer) {}
		~AutoCleanupDescriptorSetsBuffer() {}

		AutoCleanupDescriptorSetsBuffer(const AutoCleanupDescriptorSetsBuffer&) noexcept = delete;
		AutoCleanupDescriptorSetsBuffer(AutoCleanupDescriptorSetsBuffer&& other) noexcept : AutoCleanupDataBuffer(std::move(other)) {}

		AutoCleanupDescriptorSetsBuffer& operator=(const AutoCleanupDescriptorSetsBuffer&) noexcept = delete;
		AutoCleanupDescriptorSetsBuffer& operator=(AutoCleanupDescriptorSetsBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	union AccessibleHostMemoryID;

	class DeviceDataBufferSimplifierInternal
	{
		VkDevice _device;
		DeviceMemorySimplifierInternal& _memorySimplifier;

		ListTemplate<AutoCleanupShaderInputBuffer> _shaderInputs;
		ListTemplate<AutoCleanupStagingBuffer> _stagingBuffers;
		ListTemplate<AutoCleanupSmallIndexBuffer> _smallIndexBuffers;
		ListTemplate<AutoCleanupBigIndexBuffer> _bigIndexBuffers;
		ListTemplate<AutoCleanupDescriptorSetsBuffer> _descriptorSetsBuffers;

	public:
		DeviceDataBufferSimplifierInternal(VkDevice device, DeviceMemorySimplifierInternal& memorySimplifier, size_t reserve = 0x10);
		~DeviceDataBufferSimplifierInternal();

		DeviceDataBufferSimplifierInternal(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		DeviceDataBufferSimplifierInternal& operator=(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupShaderInputBuffer> AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo);
		ListObjectID<AutoCleanupStagingBuffer> AddStagingBuffer(uint64_t bufferSize);
		ListObjectID<AutoCleanupSmallIndexBuffer> AddSmallIndexBuffer(uint64_t maxIndicesAmount, bool enableTransferTo);
		ListObjectID<AutoCleanupBigIndexBuffer> AddBigIndexBuffer(uint64_t maxIndicesAmount, bool enableTransferTo);
		ListObjectID<AutoCleanupDescriptorSetsBuffer> AddDescriptorSetsBuffer(uint64_t descriptorSetSize, uint64_t descriptorSetAligment,
			uint64_t descriptorSetsAmount, bool enableTransferTo);

		void BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);

		void BindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve);
		bool TryToBindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve);

		void BindSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve);

		void BindBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve);

		void BindDescriptorSetsBuffer(ListObjectID<AutoCleanupDescriptorSetsBuffer> descriptorSetsBufferID, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindDescriptorSetsBuffer(ListObjectID<AutoCleanupDescriptorSetsBuffer> descriptorSetsBufferID, MemoryID memoryID, size_t addOnReserve);

		VkBuffer GetShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID) const;
		VkBuffer GetStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID) const;
		VkBuffer GetSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> bufferID) const;
		VkBuffer GetBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> bufferID) const;
		VkBuffer GetDescriptorSetsBuffer(ListObjectID<AutoCleanupDescriptorSetsBuffer> bufferID) const;

		void WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);
		void WriteToStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);
		void WriteToDescriptorSetsBuffer(ListObjectID<AutoCleanupDescriptorSetsBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);

		void WriteToSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> bufferID, uint64_t indicesSkipped, const uint16_t& indices, uint64_t indicesAmount, bool flushOnWrite);
		void WriteToBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> bufferID, uint64_t indicesSkipped, const uint32_t& indices, uint64_t indicesAmount, bool flushOnWrite);
	};
}
