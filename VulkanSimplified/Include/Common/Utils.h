#pragma once

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	class Utils
	{
		static VkFormat GetVertexAttributeFormat(VertexAttributeFormats attribute);
		static VkDeviceSize GetShaderInputPadding(VkDeviceSize currentSize, VertexAttributeFormats attribute);
		static VkDeviceSize GetShaderInputSize(VertexAttributeFormats attribute);

		static uint32_t GetAttributeUsedLocationsAmount(VertexAttributeFormats attribute);

	public:
		static VkDeviceSize GetShaderInputPaddedSize(const std::vector<VertexAttributeFormats>& attributes);

		static std::vector<VkVertexInputAttributeDescription> CreateAttachmentDescriptors(const std::vector<VertexAttributeFormats>& attributes, uint32_t binding);
	};
}