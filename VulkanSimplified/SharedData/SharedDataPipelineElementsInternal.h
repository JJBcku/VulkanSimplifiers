#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/SharedDataSimplifierEnums.h"

bool operator==(const VkVertexInputBindingDescription& first, const VkVertexInputBindingDescription& second);
bool operator==(const VkVertexInputAttributeDescription& first, const VkVertexInputAttributeDescription& second);
bool operator==(const VkPipelineInputAssemblyStateCreateInfo& first, const VkPipelineInputAssemblyStateCreateInfo& second);
bool operator==(const VkViewport& first, const VkViewport& second);

namespace VulkanSimplified
{
	struct VertexInputList
	{
		std::vector<ListObjectID<VkVertexInputBindingDescription>> _bindings;
		std::vector<ListObjectID<VkVertexInputAttributeDescription>> _attributes;

		bool operator==(const VertexInputList& other) const noexcept;
	};

	struct ShaderContainer;

	struct ShaderStageCreationData
	{
		ShaderStageType _stage;
		ListObjectID<ShaderContainer> _mod;
		const char* _name;
		void* _ppadding;

	public:
		ShaderStageCreationData(ShaderStageType stage, ListObjectID<ShaderContainer> mod, const char* name);
		~ShaderStageCreationData();

		bool operator==(const ShaderStageCreationData&) const noexcept = default;
	};

	class SharedDataPipelineElementsInternal
	{
		ListTemplate<ShaderStageCreationData> _shaderPipelineData;

		ListTemplate<VkVertexInputBindingDescription> _vertexInputBindingDescriptions;
		ListTemplate<VkVertexInputAttributeDescription> _vertexInputAttributeDescriptions;

		ListTemplate<VertexInputList> _vertexInputListDescriptions;

		ListTemplate<VkPipelineInputAssemblyStateCreateInfo> _pipelineInputAssembly;
		ListTemplate<VkViewport> _pipelineViewports;

	public:
		SharedDataPipelineElementsInternal(size_t reserve);
		~SharedDataPipelineElementsInternal();

		SharedDataPipelineElementsInternal(const SharedDataPipelineElementsInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& operator=(const SharedDataPipelineElementsInternal&) noexcept = delete;

		ListObjectID<ShaderStageCreationData> AddShaderPipelineData(ShaderStageType stage, ListObjectID<ShaderContainer> shader, const char* mainFunctionName);

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);

		ListObjectID<VertexInputList> AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes);

		ListObjectID<VkPipelineInputAssemblyStateCreateInfo> AddPipelineInputAssembly(TopologySetting topology);
		ListObjectID<VkViewport> AddPipelineViewport(float x, float y, uint32_t width, uint32_t height, float minDepth, float maxDepth);
	};
}
