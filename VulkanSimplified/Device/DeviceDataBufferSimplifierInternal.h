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

		AutoCleanupShaderInputBuffer& operator=(const AutoCleanupShaderInputBuffer& other) noexcept = delete;
		AutoCleanupShaderInputBuffer& operator=(AutoCleanupShaderInputBuffer&& other) noexcept
		{
			*static_cast<AutoCleanupDataBuffer*>(this) = std::move(*static_cast<AutoCleanupDataBuffer*>(&other));

			return *this;
		}
	};

	class DeviceMemorySimplifierInternal;

	class DeviceDataBufferSimplifierInternal
	{
		VkDevice _device;
		DeviceMemorySimplifierInternal& _memorySimplifier;

		ListTemplate<AutoCleanupShaderInputBuffer> _shaderInputs;

	public:
		DeviceDataBufferSimplifierInternal(VkDevice device, DeviceMemorySimplifierInternal& memorySimplifier, size_t reserve = 0x10);
		~DeviceDataBufferSimplifierInternal();

		DeviceDataBufferSimplifierInternal(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		DeviceDataBufferSimplifierInternal& operator=(const DeviceDataBufferSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupShaderInputBuffer> AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo);

		void BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);
		bool TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve);

		VkBuffer GetShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID) const;

		void WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite);
	};
}
