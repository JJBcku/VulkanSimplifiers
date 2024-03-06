#pragma once

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	class Utils
	{
	public:
		static VkDeviceSize GetShaderInputPadding(VkDeviceSize currentSize, VertexAttributeFormats attribute);
		static VkDeviceSize GetShaderInputPaddedSize(const std::vector<VertexAttributeFormats>& attributes);
	};
}