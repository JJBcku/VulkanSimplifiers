#pragma once

namespace VulkanSimplified
{
	class DeviceDataBufferSimplifierInternal;

	template<class T>
	class ListObjectID;

	class AutoCleanupShaderInputBuffer;

	union MemoryID;
	struct MemoryObject;

	enum class VertexAttributeFormats : uint64_t;

	class DeviceDataBufferSimplifier
	{
		DeviceDataBufferSimplifierInternal& _internal;

	public:
		DeviceDataBufferSimplifier(DeviceDataBufferSimplifierInternal& ref);
		~DeviceDataBufferSimplifier();

		DeviceDataBufferSimplifier& operator=(const DeviceDataBufferSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanupShaderInputBuffer> AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo);

		ListObjectID<MemoryObject> BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
		std::optional<ListObjectID<MemoryObject>> TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
	};
}
