#pragma once

namespace VulkanSimplified
{
	class DeviceDataBufferSimplifierInternal;

	template<class T>
	class ListObjectID;

	class AutoCleanupShaderInputBuffer;

	union MemoryID;

	enum class VertexAttributeFormats : uint64_t;

	class DeviceDataBufferSimplifier
	{
		DeviceDataBufferSimplifierInternal& _internal;

	public:
		DeviceDataBufferSimplifier(DeviceDataBufferSimplifierInternal& ref);
		~DeviceDataBufferSimplifier();

		DeviceDataBufferSimplifier& operator=(const DeviceDataBufferSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanupShaderInputBuffer> AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo);

		void BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);

		void WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite = false);
	};
}
