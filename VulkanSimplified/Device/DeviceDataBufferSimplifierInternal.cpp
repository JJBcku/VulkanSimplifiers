#include "../Other/pch.h"
#include "DeviceDataBufferSimplifierInternal.h"
#include "DeviceMemorySimplifierInternal.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

#include "../Include/Common/Utils.h"

namespace VulkanSimplified
{

	AutoCleanupDataBuffer::AutoCleanupDataBuffer(VkDevice device, VkBuffer dataBuffer) : _device(device), _ppadding(nullptr), _dataBuffer(dataBuffer)
	{
		vkGetBufferMemoryRequirements(device, dataBuffer, &_memReq);
	}

	AutoCleanupDataBuffer::~AutoCleanupDataBuffer()
	{
		if (_dataBuffer != VK_NULL_HANDLE)
			vkDestroyBuffer(_device, _dataBuffer, nullptr);
	}

	AutoCleanupDataBuffer::AutoCleanupDataBuffer(AutoCleanupDataBuffer&& other) noexcept : _device(other._device), _ppadding(nullptr),
		_dataBuffer(other._dataBuffer), _memReq(other._memReq), _boundID(other._boundID)
	{
		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._memReq = VkMemoryRequirements();
		other._boundID.reset();
	}

	AutoCleanupDataBuffer& AutoCleanupDataBuffer::operator=(AutoCleanupDataBuffer&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_dataBuffer = other._dataBuffer;
		_memReq = other._memReq;
		_boundID = other._boundID;

		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._memReq = VkMemoryRequirements();
		other._boundID.reset();

		return *this;
	}

	VkBuffer AutoCleanupDataBuffer::GetBuffer() const
	{
		return _dataBuffer;
	}

	VkMemoryRequirements AutoCleanupDataBuffer::GetRequirements() const
	{
		return _memReq;
	}

	std::optional<std::pair<MemoryID, ListObjectID<MemoryObject>>> AutoCleanupDataBuffer::GetBuffersBindingID() const
	{
		return _boundID;
	}

	bool AutoCleanupDataBuffer::IsBufferBound() const
	{
		return _boundID.has_value();
	}

	void AutoCleanupDataBuffer::BindBuffer(DeviceMemorySimplifierInternal& memoryData, MemoryID memoryID, size_t addOnReserve)
	{
		auto suballocationID = memoryData.BindBuffer(memoryID, _dataBuffer, _memReq, addOnReserve);

		_boundID = { memoryID, suballocationID };
	}

	bool AutoCleanupDataBuffer::TryToBindBuffer(DeviceMemorySimplifierInternal& memoryData, MemoryID memoryID, size_t addOnReserve)
	{
		auto suballocationID = memoryData.TryToBindBuffer(memoryID, _dataBuffer, _memReq, addOnReserve);

		if (suballocationID.has_value())
		{
			_boundID = { memoryID, suballocationID.value() };
		}

		return suballocationID.has_value();
	}

	DeviceDataBufferSimplifierInternal::DeviceDataBufferSimplifierInternal(VkDevice device, DeviceMemorySimplifierInternal& memorySimplifier, size_t reserve) : _device(device),
		_memorySimplifier(memorySimplifier), _shaderInputs(reserve)
	{
	}

	DeviceDataBufferSimplifierInternal::~DeviceDataBufferSimplifierInternal()
	{
	}

	ListObjectID<AutoCleanupShaderInputBuffer> DeviceDataBufferSimplifierInternal::AddShaderInputBuffer(const std::vector<VertexAttributeFormats>& vertexAttributes, uint32_t maxVertexAmount, bool enableTransferTo)
	{
		VkBuffer add = VK_NULL_HANDLE;

		auto inputSize = Utils::GetShaderInputPaddedSize(vertexAttributes);

		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		createInfo.size = inputSize * maxVertexAmount;

		if (enableTransferTo)
			createInfo.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceDataBufferSimplifierInternal::AddShaderInputBuffer Error: Program failed to create the buffer!");

		return _shaderInputs.AddObject(AutoCleanupShaderInputBuffer(_device, add));
	}

	ListObjectID<AutoCleanupStagingBuffer> DeviceDataBufferSimplifierInternal::AddStagingBuffer(uint64_t bufferSize)
	{
		VkBuffer add = VK_NULL_HANDLE;

		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		createInfo.size = bufferSize;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceDataBufferSimplifierInternal::AddStagingBuffer Error: Program failed to create the buffer!");

		return _stagingBuffers.AddObject(AutoCleanupStagingBuffer(_device, add));
	}

	void DeviceDataBufferSimplifierInternal::BindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		auto& shaderInput = _shaderInputs.GetObject(_shaderInputBuffer);

		shaderInput.BindBuffer(_memorySimplifier, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifierInternal::TryToBindShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> _shaderInputBuffer, MemoryID memoryID, size_t addOnReserve)
	{
		auto& shaderInput = _shaderInputs.GetObject(_shaderInputBuffer);

		return shaderInput.TryToBindBuffer(_memorySimplifier, memoryID, addOnReserve);
	}

	void DeviceDataBufferSimplifierInternal::BindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve)
	{
		auto& stagingBuffer = _stagingBuffers.GetObject(_stagingBufferID);

		stagingBuffer.BindBuffer(_memorySimplifier, memoryID, addOnReserve);
	}

	bool DeviceDataBufferSimplifierInternal::TryToBindStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> _stagingBufferID, AccessibleHostMemoryID memoryID, size_t addOnReserve)
	{
		auto& stagingBuffer = _stagingBuffers.GetObject(_stagingBufferID);

		return stagingBuffer.TryToBindBuffer(_memorySimplifier, memoryID, addOnReserve);
	}

	VkBuffer DeviceDataBufferSimplifierInternal::GetShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID) const
	{
		auto& buffer = _shaderInputs.GetConstObject(bufferID);

		return buffer.GetBuffer();
	}

	VkBuffer DeviceDataBufferSimplifierInternal::GetStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID) const
	{
		auto& buffer = _stagingBuffers.GetConstObject(bufferID);

		return buffer.GetBuffer();
	}

	void DeviceDataBufferSimplifierInternal::WriteToShaderInputBuffer(ListObjectID<AutoCleanupShaderInputBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite)
	{
		auto& buffer = _shaderInputs.GetConstObject(bufferID);

		auto binding = buffer.GetBuffersBindingID();

		if (binding.has_value())
		{
			auto& memory = binding.value().first;
			auto& suballocation = binding.value().second;
			
			_memorySimplifier.WriteToMemoryObject(memory, suballocation, offset, data, dataSize, flushOnWrite);
		}
		else
			throw std::runtime_error("DeviceDataBufferSimplifierInternal::WriteToShaderInputBuffer Error: Program tried to write data to an unbound buffer!");
	}

	void DeviceDataBufferSimplifierInternal::WriteToStagingBuffer(ListObjectID<AutoCleanupStagingBuffer> bufferID, uint64_t offset, const char& data, uint64_t dataSize, bool flushOnWrite)
	{
		auto& buffer = _stagingBuffers.GetConstObject(bufferID);

		auto binding = buffer.GetBuffersBindingID();

		if (binding.has_value())
		{
			auto& memory = binding.value().first;
			auto& suballocation = binding.value().second;

			_memorySimplifier.WriteToMemoryObject(memory, suballocation, offset, data, dataSize, flushOnWrite);
		}
		else
			throw std::runtime_error("DeviceDataBufferSimplifierInternal::WriteToStagingBuffer Error: Program tried to write data to an unbound buffer!");
	}

}