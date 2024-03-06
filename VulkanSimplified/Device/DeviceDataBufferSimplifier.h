#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	class AutoCleanupShaderInputBuffer
	{
		VkDevice _device;
		void* _ppadding;
		VkBuffer _dataBuffer;
		VkDeviceSize _size;
		VkDeviceSize _aligmentReq;

	public:
		AutoCleanupShaderInputBuffer(VkDevice device, VkBuffer dataBuffer, VkDeviceSize size, VkDeviceSize aligmentReq);
		~AutoCleanupShaderInputBuffer();

		AutoCleanupShaderInputBuffer(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer(AutoCleanupShaderInputBuffer&& other) noexcept;

		AutoCleanupShaderInputBuffer& operator=(const AutoCleanupShaderInputBuffer&) noexcept = delete;
		AutoCleanupShaderInputBuffer& operator=(AutoCleanupShaderInputBuffer&& other) noexcept;
	};

	class DeviceDataBufferSimplifier
	{
		ListTemplate<AutoCleanupShaderInputBuffer>
	};
}
