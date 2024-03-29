#include "../Other/pch.h"
#include "DeviceDataBufferSimplifierInternal.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

#include "../Include/Common/Utils.h"

namespace VulkanSimplified
{

	AutoCleanupShaderInputBuffer::AutoCleanupShaderInputBuffer(VkDevice device, VkBuffer dataBuffer) : _device(device), _ppadding(nullptr),
		_dataBuffer(dataBuffer)
	{
		vkGetBufferMemoryRequirements(device, dataBuffer, &_memReq);
	}

	AutoCleanupShaderInputBuffer::~AutoCleanupShaderInputBuffer()
	{
		if (_dataBuffer != VK_NULL_HANDLE)
			vkDestroyBuffer(_device, _dataBuffer, nullptr);
	}

	AutoCleanupShaderInputBuffer::AutoCleanupShaderInputBuffer(AutoCleanupShaderInputBuffer&& other) noexcept : _device(other._device), _ppadding(nullptr),
		_dataBuffer(other._dataBuffer), _memReq(other._memReq), _boundID(other._boundID)
	{
		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._memReq = VkMemoryRequirements();
		other._boundID = std::optional<std::pair<MemoryID, MemoryObject>>();
	}

	AutoCleanupShaderInputBuffer& AutoCleanupShaderInputBuffer::operator=(AutoCleanupShaderInputBuffer&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_dataBuffer = other._dataBuffer;
		_memReq = other._memReq;
		_boundID = other._boundID;

		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._memReq = VkMemoryRequirements();
		other._boundID = std::optional<std::pair<MemoryID, MemoryObject>>();

		return *this;
	}

	DeviceDataBufferSimplifierInternal::DeviceDataBufferSimplifierInternal(VkDevice device, size_t reserve) : _device(device), _ppadding(nullptr), _shaderInputs(reserve)
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
			throw std::runtime_error("DeviceDataBufferSimplifierInternal::AddShaderInputBuffer Error: Program failed to create a buffer!");

		return _shaderInputs.AddObject(AutoCleanupShaderInputBuffer(_device, add));
	}

}