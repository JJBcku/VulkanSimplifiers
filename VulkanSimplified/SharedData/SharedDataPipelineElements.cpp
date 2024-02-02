#include "../pch.h"
#include "../Include/SharedDataPipelineElements.h"

#include "SharedDataPipelineElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineElements::SharedDataPipelineElements(SharedDataPipelineElementsInternal& ref) : _internal(ref)
	{
	}

	SharedDataPipelineElements::~SharedDataPipelineElements()
	{
	}

	ListObjectID<ShaderStageCreationData> SharedDataPipelineElements::AddShaderPipelineData(ShaderStageType stage, ListObjectID<ShaderContainer> shader, const char* mainFunctionName)
	{
		return _internal.AddShaderPipelineData(stage, shader, mainFunctionName);
	}

	ListObjectID<VkVertexInputBindingDescription> SharedDataPipelineElements::AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex)
	{
		return _internal.AddBindingDescription(binding, stride, useInstanceIndex);
	}

	ListObjectID<VkVertexInputAttributeDescription> SharedDataPipelineElements::AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset)
	{
		return _internal.AddAttributeDescription(location, binding, format, offset);
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

}
