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

}
