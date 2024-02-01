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

}
