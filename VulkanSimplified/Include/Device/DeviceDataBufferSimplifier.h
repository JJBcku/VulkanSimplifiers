#pragma once

namespace VulkanSimplified
{
	class DeviceDataBufferSimplifierInternal;

	template<class T>
	class ListObjectID;

	class AutoCleanupShaderInputBuffer;
	class AutoCleanupStagingBuffer;

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

		void BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);

		void BindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve);
		bool TryToBindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve);

		void WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite = false);
		void WriteToStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite = false);
	};
}
