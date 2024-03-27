#pragma once

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

union VkClearValue;
union VkClearColorValue;
struct VkClearDepthStencilValue;

namespace VulkanSimplified
{
	class SharedDataPipelineElementsInternal;

	struct VertexInputList;
	struct ShaderContainer;
	struct ShaderStageCreationData;
	struct PipelineViewportsStateList;
	struct ColorBlendSettings;

	template<class T>
	class ListObjectID;

	class SharedDataPipelineElements
	{
		SharedDataPipelineElementsInternal& _internal;

	public:
		SharedDataPipelineElements(SharedDataPipelineElementsInternal& ref);
		~SharedDataPipelineElements();

		SharedDataPipelineElements& operator=(const SharedDataPipelineElements&) noexcept = delete;

		ListObjectID<ShaderStageCreationData> AddShaderPipelineData(ShaderStageType stage, const char* mainFunctionName);

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);
		std::vector<ListObjectID<VkVertexInputAttributeDescription>> AddAttributeDescriptions(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes);

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

		ListObjectID<VkClearValue> AddClearColorValue(float r, float g, float b, float a);
		ListObjectID<VkClearValue> AddClearColorValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
		ListObjectID<VkClearValue> AddClearColorValue(int32_t r, int32_t g, int32_t b, int32_t a);

		ListObjectID<VkClearValue> AddClearDepthValue(float depth, uint32_t stencil = 0);
	};
}

