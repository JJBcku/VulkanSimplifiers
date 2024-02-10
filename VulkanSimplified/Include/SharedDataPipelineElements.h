#pragma once

#include "VulkanSimplifierListTemplate.h"
#include "SharedDataSimplifierEnums.h"

struct VkVertexInputBindingDescription;
struct VkVertexInputAttributeDescription;

struct VkPipelineInputAssemblyStateCreateInfo;
struct VkPipelineRasterizationStateCreateInfo;
struct VkPipelineMultisampleStateCreateInfo;
struct VkPipelineDepthStencilStateCreateInfo;
struct VkPipelineColorBlendAttachmentState;

struct VkViewport;
struct VkRect2D;

namespace VulkanSimplified
{
	class SharedDataPipelineElementsInternal;

	struct VertexInputList;
	struct ShaderContainer;
	struct ShaderStageCreationData;
	struct PipelineViewportsStateList;
	struct ColorBlendSettings;

	class SharedDataPipelineElements
	{
		SharedDataPipelineElementsInternal& _internal;

	public:
		SharedDataPipelineElements(SharedDataPipelineElementsInternal& ref);
		~SharedDataPipelineElements();

		SharedDataPipelineElements& operator=(const SharedDataPipelineElements&) noexcept = delete;

		ListObjectID<ShaderStageCreationData> AddShaderPipelineData(ShaderStageType stage, const char* mainFunctionName);

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);

		ListObjectID<VertexInputList> AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes);

		ListObjectID<VkPipelineInputAssemblyStateCreateInfo> AddPipelineInputAssembly(TopologySetting topology);
		ListObjectID<VkPipelineRasterizationStateCreateInfo> AddPipelineRasterizationState(PipelinePolygonMode polygonMode, PipelineCullMode cullMode, bool clockwiseFront);
		ListObjectID<VkPipelineMultisampleStateCreateInfo> AddPipelineMultisampleState(PipelineMultisampleCount multisampling, bool sampleShading, float minSampleShading);
		ListObjectID<VkPipelineDepthStencilStateCreateInfo> AddPipelineDepthState(bool depthTest, bool depthWrite, PipelineDepthCompare compare);
		ListObjectID<VkPipelineColorBlendAttachmentState> AddPipelineColorBlendAttachment(PipelineBlendSettings settings);
		ListObjectID<ColorBlendSettings> AddPipelineColorBlendState(const std::vector<ListObjectID<VkPipelineColorBlendAttachmentState>>& attachments, float blendConstantR = 0.0f, float blendConstantG = 0.0f, float blendConstantB = 0.0f, float blendConstantA = 0.0f);

		ListObjectID<VkViewport> AddPipelineViewport(float x, float y, uint32_t width, uint32_t height, float minDepth, float maxDepth);
		ListObjectID<VkRect2D> AddPipelineScissor(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height);
		ListObjectID<PipelineViewportsStateList> AddPipelineViewportState(const std::vector<std::pair<ListObjectID<VkViewport>, ListObjectID<VkRect2D>>>& viewportScissorPairs);
	};
}

