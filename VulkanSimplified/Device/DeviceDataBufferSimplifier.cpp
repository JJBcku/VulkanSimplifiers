#include "../Other/pch.h"
#include "DeviceDataBufferSimplifier.h"

#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{

	AutoCleanupShaderInputBuffer::AutoCleanupShaderInputBuffer(VkDevice device, VkBuffer dataBuffer, VkDeviceSize size, VkDeviceSize aligmentReq) : _device(device), _ppadding(nullptr),
		_dataBuffer(dataBuffer), _size(size), _aligmentReq(aligmentReq)
	{
	}

	AutoCleanupShaderInputBuffer::~AutoCleanupShaderInputBuffer()
	{
		if (_dataBuffer != VK_NULL_HANDLE)
			vkDestroyBuffer(_device, _dataBuffer, nullptr);
	}

	AutoCleanupShaderInputBuffer::AutoCleanupShaderInputBuffer(AutoCleanupShaderInputBuffer&& other) noexcept : _device(other._device), _ppadding(nullptr),
		_dataBuffer(other._dataBuffer), _size(other._size), _aligmentReq(other._aligmentReq)
	{
		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._size = 0;
		other._aligmentReq = 0;
	}

	AutoCleanupShaderInputBuffer& AutoCleanupShaderInputBuffer::operator=(AutoCleanupShaderInputBuffer&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_dataBuffer = other._dataBuffer;
		_size = other._size;
		_aligmentReq = other._aligmentReq;

		other._device = VK_NULL_HANDLE;
		other._dataBuffer = VK_NULL_HANDLE;
		other._size = 0;
		other._aligmentReq = 0;

		return *this;
	}

}