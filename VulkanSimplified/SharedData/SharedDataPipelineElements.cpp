#include "../Other/pch.h"
#include "../Include/SharedData/SharedDataPipelineElements.h"

#include "SharedDataPipelineElementsInternal.h"

#include "../Include/Common/ListObjectID.h"

namespace VulkanSimplified
{

	SharedDataPipelineElements::SharedDataPipelineElements(SharedDataPipelineElementsInternal& ref) : _internal(ref)
	{
	}

	SharedDataPipelineElements::~SharedDataPipelineElements()
	{
	}

	ListObjectID<ShaderStageCreationData> SharedDataPipelineElements::AddShaderPipelineData(ShaderStageType stage, const char* mainFunctionName)
	{
		return _internal.AddShaderPipelineData(stage, mainFunctionName);
	}

	ListObjectID<VkVertexInputBindingDescription> SharedDataPipelineElements::AddBindingDescription(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes, bool useInstanceIndex)
	{
		return _internal.AddBindingDescription(binding, attributes, useInstanceIndex);
	}

	ListObjectID<VkVertexInputAttributeDescription> SharedDataPipelineElements::AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset)
	{
		return _internal.AddAttributeDescription(location, binding, format, offset);
	}

	std::vector<ListObjectID<VkVertexInputAttributeDescription>> SharedDataPipelineElements::AddAttributeDescriptions(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes)
	{
		return _internal.AddAttributeDescriptions(binding, attributes);
	}

	ListObjectID<VertexInputList> SharedDataPipelineElements::AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes)
	{
		return _internal.AddVertexInputList(bindings, attributes);
	}

	ListObjectID<VkPipelineInputAssemblyStateCreateInfo> SharedDataPipelineElements::AddPipelineInputAssembly(TopologySetting topology)
	{
		return _internal.AddPipelineInputAssembly(topology);
	}

	ListObjectID<VkPipelineRasterizationStateCreateInfo> SharedDataPipelineElements::AddPipelineRasterizationState(PipelinePolygonMode polygonMode, PipelineCullMode cullMode, bool clockwiseFront)
	{
		return _internal.AddPipelineRasterizationState(polygonMode, cullMode, clockwiseFront);
	}

	ListObjectID<VkPipelineMultisampleStateCreateInfo> SharedDataPipelineElements::AddPipelineMultisampleState(PipelineMultisampleCount multisampling, bool sampleShading, float minSampleShading)
	{
		return _internal.AddPipelineMultisampleState(multisampling, sampleShading, minSampleShading);
	}

	ListObjectID<VkPipelineDepthStencilStateCreateInfo> SharedDataPipelineElements::AddPipelineDepthState(bool depthTest, bool depthWrite, PipelineDepthCompare compare)
	{
		return _internal.AddPipelineDepthState(depthTest, depthWrite, compare);
	}

	ListObjectID<VkPipelineColorBlendAttachmentState> SharedDataPipelineElements::AddPipelineColorBlendAttachment(PipelineBlendSettings settings)
	{
		return _internal.AddPipelineColorBlendAttachment(settings);
	}

	ListObjectID<ColorBlendSettings> SharedDataPipelineElements::AddPipelineColorBlendState(const std::vector<ListObjectID<VkPipelineColorBlendAttachmentState>>& attachments, float blendConstantR, float blendConstantG, float blendConstantB, float blendConstantA)
	{
		return _internal.AddPipelineColorBlendState(attachments, blendConstantR, blendConstantG, blendConstantB, blendConstantA);
	}

	ListObjectID<VkViewport> SharedDataPipelineElements::AddPipelineViewport(float x, float y, uint32_t width, uint32_t height, float minDepth, float maxDepth)
	{
		return _internal.AddPipelineViewport(x, y, width, height, minDepth, maxDepth);
	}

	ListObjectID<VkRect2D> SharedDataPipelineElements::AddPipelineScissor(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height)
	{
		return _internal.AddPipelineScissor(offsetX, offsetY, width, height);
	}

	ListObjectID<PipelineViewportsStateList> SharedDataPipelineElements::AddPipelineViewportState(const std::vector<std::pair<ListObjectID<VkViewport>, ListObjectID<VkRect2D>>>& viewportScissorPairs)
	{
		return _internal.AddPipelineViewportState(viewportScissorPairs);
	}

	ListObjectID<VkClearValue> SharedDataPipelineElements::AddClearColorValue(float r, float g, float b, float a)
	{
		return _internal.AddClearColorValue(r, g, b, a);
	}

	ListObjectID<VkClearValue> SharedDataPipelineElements::AddClearColorValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
	{
		return _internal.AddClearColorValue(r, g, b, a);
	}

	ListObjectID<VkClearValue> SharedDataPipelineElements::AddClearColorValue(int32_t r, int32_t g, int32_t b, int32_t a)
	{
		return _internal.AddClearColorValue(r, g, b, a);
	}

	ListObjectID<VkClearValue> SharedDataPipelineElements::AddClearDepthValue(float depth, uint32_t stencil)
	{
		return _internal.AddClearDepthValue(depth, stencil);
	}

}
