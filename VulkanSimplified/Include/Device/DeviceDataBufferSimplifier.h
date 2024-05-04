#pragma once

namespace VulkanSimplified
{
	class DeviceDataBufferSimplifierInternal;

	template<class T>
	class ListObjectID;

	class AutoCleanupShaderInputBuffer;
	class AutoCleanupStagingBuffer;
	class AutoCleanupSmallIndexBuffer;
	class AutoCleanupBigIndexBuffer;
	class AutoCleanupDescriptorSetsBuffer;

	union MemoryID;
	union AccessibleHostMemoryID;

	enum class VertexAttributeFormats : uint64_t;

	class DeviceDataBufferSimplifier
	{
		DeviceDataBufferSimplifierInternal& _internal;

	public:
		DeviceDataBufferSimplifier(DeviceDataBufferSimplifierInternal& ref);
		~DeviceDataBufferSimplifier();

		DeviceDataBufferSimplifier& operator=(const DeviceDataBufferSimplifier&) noexcept = delete;

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

		void WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);
		void WriteToStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);
		void WriteToDescriptorSetsBuffer(ListObjectID<AutoCleanupDescriptorSetsBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite);

		void WriteToSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> bufferID, uint64_t indicesSkipped, const uint16_t& indices, uint64_t indicesAmount, bool flushOnWrite);
		void WriteToBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> bufferID, uint64_t indicesSkipped, const uint32_t& indices, uint64_t indicesAmount, bool flushOnWrite);
	};
}
