#pragma once

namespace VulkanSimplified
{
	enum class VertexAttributeFormats : uint64_t;

	class Utils
	{
		static VkFormat GetVertexAttributeFormat(VertexAttributeFormats attribute);
		static uint64_t GetShaderInputPadding(uint64_t currentSize, VertexAttributeFormats attribute);
		static uint64_t GetShaderInputSize(VertexAttributeFormats attribute);

		static uint32_t GetAttributeUsedLocationsAmount(VertexAttributeFormats attribute);

	public:
		static uint64_t GetShaderInputPaddedSize(const std::vector<VertexAttributeFormats>& attributes);

		static std::vector<VkVertexInputAttributeDescription> CreateAttachmentDescriptors(const std::vector<VertexAttributeFormats>& attributes, uint32_t binding);
	};
}