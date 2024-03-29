#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"
#include "DeviceMemorySimplifierInternal.h"

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	class AutoCleanupShaderInputBuffer
	{
		VkDevice _device;
		void* _ppadding;
		VkBuffer _dataBuffer;
		VkMemoryRequirements _memReq;
		std::optional<std::pair<MemoryID, MemoryObject>> _boundID;

	public:
		AutoCleanupShaderInputBuffer(VkDevice device, VkBuffer dataBuffer);
		~AutoCleanupShaderInputBuffer();

		AutoCleanupShaderInputBuffer(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer(AutoCleanupShaderInputBuffer&& other) noexcept;

		AutoCleanupShaderInputBuffer& operator=(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer& operator=(AutoCleanupShaderInputBuffer&& other) noexcept;
	};

	class DeviceDataBufferSimplifierInternal
	{
		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupShaderInputBuffer> _shaderInputs;

	public:
		DeviceDataBufferSimplifierInternal(VkDevice device, size_t reserve = 0x10);
		~DeviceDataBufferSimplifierInternal();

		DeviceDataBufferSimplifierInternal(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		DeviceDataBufferSimplifierInternal& operator=(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupShaderInputBuffer> AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo);
	};
}
