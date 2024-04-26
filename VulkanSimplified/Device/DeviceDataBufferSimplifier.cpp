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

	void DeviceDataBufferSimplifier::BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		_internal.BindShaderInputBuffer(_shaderInputBuffer, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifier::TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		return _internal.TryToBindShaderInputBuffer(_shaderInputBuffer, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifier::WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		_internal.WriteToShaderInputBuffer(bufferID, offset, data, dataSize, flushOnWrite);
	}

}
