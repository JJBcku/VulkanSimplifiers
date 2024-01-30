#pragma once

struct VkVertexInputBindingDescription;

#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;

	class SharedDataSimplifierCore
	{
		std::unique_ptr<SharedDataSimplifierCoreInternal> _internal;

	public:
		SharedDataSimplifierCore(size_t reserveListElements);
		~SharedDataSimplifierCore();

		SharedDataSimplifierCore(const SharedDataSimplifierCore&) noexcept = delete;
		
		SharedDataSimplifierCore& operator=(const SharedDataSimplifierCore&) noexcept = delete;

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
	};
}


