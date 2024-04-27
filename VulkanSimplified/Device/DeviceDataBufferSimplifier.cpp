#include "../Other/pch.h"
#include "../Include/Device/DeviceDataBufferSimplifier.h"

#include "../Include/Common/ListObjectID.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"

#include "DeviceDataBufferSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceDataBufferSimplifier::DeviceDataBufferSimplifier(DeviceDataBufferSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceDataBufferSimplifier::~DeviceDataBufferSimplifier()
	{
	}

	ListObjectID<AutoCleanupShaderInputBuffer> DeviceDataBufferSimplifier::AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo)
	{
		return _internal.AddShaderInputBuffer(vertexAttributes, maxVertexAmount, enableTransferTo);
	}

	ListObjectID<AutoCleanupStagingBuffer> DeviceDataBufferSimplifier::AddStagingBuffer(uint64_t bufferSize)
	{
		return _internal.AddStagingBuffer(bufferSize);
	}

	ListObjectID<AutoCleanupSmallIndexBuffer> DeviceDataBufferSimplifier::AddSmallIndexBuffer(uint64_t maxIndicesAmount, bool enableTransferTo)
	{
		return _internal.AddSmallIndexBuffer(maxIndicesAmount, enableTransferTo);
	}

	ListObjectID<AutoCleanupBigIndexBuffer> DeviceDataBufferSimplifier::AddBigIndexBuffer(uint64_t maxIndicesAmount, bool enableTransferTo)
	{
		return _internal.AddBigIndexBuffer(maxIndicesAmount, enableTransferTo);
	}

	void DeviceDataBufferSimplifier::BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		_internal.BindShaderInputBuffer(_shaderInputBuffer, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifier::TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		return _internal.TryToBindShaderInputBuffer(_shaderInputBuffer, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifier::BindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve)
	{
		_internal.BindStagingBuffer(_stagingBufferID, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifier::TryToBindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve)
	{
		return _internal.TryToBindStagingBuffer(_stagingBufferID, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifier::BindSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve)
	{
		_internal.BindSmallIndexBuffer(indexBufferID, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifier::TryToBindSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve)
	{
		return _internal.TryToBindSmallIndexBuffer(indexBufferID, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifier::BindBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve)
	{
		_internal.BindBigIndexBuffer(indexBufferID, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifier::TryToBindBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> indexBufferID, MemoryID memoryID, size_t addOnReserve)
	{
		return _internal.TryToBindBigIndexBuffer(indexBufferID, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifier::WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite)
	{
		_internal.WriteToShaderInputBuffer(bufferID, offset, data, dataSize, flushOnWrite);
	}

	void DeviceDataBufferSimplifier::WriteToStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite)
	{
		_internal.WriteToStagingBuffer(bufferID, offset, data, dataSize, flushOnWrite);
	}

	void DeviceDataBufferSimplifier::WriteToSmallIndexBuffer(ListObjectID<AutoCleanupSmallIndexBuffer> bufferID, uint64_t indicesSkipped, const uint16_t& indices,
		uint64_t indicesAmount, bool flushOnWrite)
	{
		_internal.WriteToSmallIndexBuffer(bufferID, indicesSkipped, indices, indicesAmount, flushOnWrite);
	}

	void DeviceDataBufferSimplifier::WriteToBigIndexBuffer(ListObjectID<AutoCleanupBigIndexBuffer> bufferID, uint64_t indicesSkipped, const uint32_t& indices, uint64_t indicesAmount,
		bool flushOnWrite)
	{
		_internal.WriteToBigIndexBuffer(bufferID, indicesSkipped, indices, indicesAmount, flushOnWrite);
	}

}
