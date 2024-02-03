#include "../pch.h"
#include "SharedDataPipelineElementsInternal.h"

//#include "../Device/ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineElementsInternal::SharedDataPipelineElementsInternal(size_t reserve) : _shaderPipelineData(reserve), _vertexInputBindingDescriptions(reserve),
		_vertexInputAttributeDescriptions(reserve), _vertexInputListDescriptions(reserve), _pipelineInputAssembly(reserve), _pipelineRasterizationStates(reserve),
		_pipelineMultiSampleStates(reserve), _pipelineViewports(reserve), _pipelineScissors(reserve), _pipelineViewportStates(reserve)
	{
	}

	SharedDataPipelineElementsInternal::~SharedDataPipelineElementsInternal()
	{
	}

	ListObjectID<ShaderStageCreationData> SharedDataPipelineElementsInternal::AddShaderPipelineData(ShaderStageType stage, ListObjectID<ShaderContainer> shader, const char* mainFunctionName)
	{
		return _shaderPipelineData.AddUniqueObject(ShaderStageCreationData(stage, shader, mainFunctionName));
	}

	ListObjectID<VkVertexInputBindingDescription> SharedDataPipelineElementsInternal::AddBindingDescription(uint32_t binding, uint32_t stride, bool useInstanceIndex)
	{
		VkVertexInputBindingDescription add{};
		add.binding = binding;
		add.stride = stride;
		add.inputRate = useInstanceIndex ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;

		return _vertexInputBindingDescriptions.AddUniqueObject(add);
	}

	ListObjectID<VkVertexInputAttributeDescription> SharedDataPipelineElementsInternal::AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset)
	{
		VkVertexInputAttributeDescription add{};
		add.location = location;
		add.binding = binding;
		add.format = VK_FORMAT_MAX_ENUM;
		add.offset = offset;

		switch (format)
		{
		case VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT:
			add.format = VK_FORMAT_R32G32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC2_DOUBLE:
			add.format = VK_FORMAT_R64G64_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT:
			add.format = VK_FORMAT_R32G32B32A32_SFLOAT;
			break;
		case VulkanSimplified::VertexAttributeFormats::VEC4_DOUBLE:
			add.format = VK_FORMAT_R64G64B64A64_SFLOAT;
			break;
		default:
			throw std::runtime_error("AddAttributeDescription Error: Program used erroneous vertex attribute format!");
		}

		return _vertexInputAttributeDescriptions.AddUniqueObject(add);
	}

	ListObjectID<VertexInputList> SharedDataPipelineElementsInternal::AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes)
	{
		VertexInputList add;

		add._attributes = attributes;
		add._bindings = bindings;

		return _vertexInputListDescriptions.AddUniqueObject(std::move(add));
	}

	ListObjectID<VkPipelineInputAssemblyStateCreateInfo> SharedDataPipelineElementsInternal::AddPipelineInputAssembly(TopologySetting topology)
	{
		VkPipelineInputAssemblyStateCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		add.primitiveRestartEnable = VK_FALSE;
		
		switch (topology)
		{
		case VulkanSimplified::TopologySetting::POINT:
			add.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			break;
		case VulkanSimplified::TopologySetting::LINE:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			break;
		case VulkanSimplified::TopologySetting::LINE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			break;
		case VulkanSimplified::TopologySetting::LINE_STRIP_RESTARTABLE:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			add.primitiveRestartEnable = VK_TRUE;
			break;
		case VulkanSimplified::TopologySetting::TRIANGLE:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
		case VulkanSimplified::TopologySetting::TRIANGLE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			break;
		case VulkanSimplified::TopologySetting::TRIANGLE_STRIP_RESTARTABLE:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			add.primitiveRestartEnable = VK_TRUE;
			break;
		case VulkanSimplified::TopologySetting::TRIANGLE_FAN:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			break;
		case VulkanSimplified::TopologySetting::TRIANGLE_FAN_RESTARTABLE:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			add.primitiveRestartEnable = VK_TRUE;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineElementsInternal::AddPipelineInputAssembly Error: Program was given an erroneous topology setting value!");
		}

		return _pipelineInputAssembly.AddUniqueObject(add);
	}

	ListObjectID<VkPipelineRasterizationStateCreateInfo> SharedDataPipelineElementsInternal::AddPipelineRasterizationState(PipelinePolygonMode polygonMode, PipelineCullMode cullMode, bool clockwiseFront)
	{
		VkPipelineRasterizationStateCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		add.lineWidth = 1.0f;

		switch (polygonMode)
		{
		case VulkanSimplified::PipelinePolygonMode::FILL:
			add.polygonMode = VK_POLYGON_MODE_FILL;
			break;
		case VulkanSimplified::PipelinePolygonMode::LINE:
			add.polygonMode = VK_POLYGON_MODE_LINE;
			break;
		case VulkanSimplified::PipelinePolygonMode::POINT:
			add.polygonMode = VK_POLYGON_MODE_POINT;
			break;
		case VulkanSimplified::PipelinePolygonMode::RECTANGLE_NV:
			add.polygonMode = VK_POLYGON_MODE_FILL_RECTANGLE_NV;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineElementsInternal::AddPipelineRasterizationState Error: Program was given an erroneous polygon mode!");
		}

		switch (cullMode)
		{
		case VulkanSimplified::PipelineCullMode::OFF:
			add.cullMode = VK_CULL_MODE_NONE;
			break;
		case VulkanSimplified::PipelineCullMode::FRONT:
			add.cullMode = VK_CULL_MODE_FRONT_BIT;
			break;
		case VulkanSimplified::PipelineCullMode::BACK:
			add.cullMode = VK_CULL_MODE_BACK_BIT;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineElementsInternal::AddPipelineRasterizationState Error: Program was given an erroneous cull mode!");
		}

		add.frontFace = clockwiseFront ? VK_FRONT_FACE_CLOCKWISE : VK_FRONT_FACE_COUNTER_CLOCKWISE;

		return _pipelineRasterizationStates.AddUniqueObject(add);
	}

	ListObjectID<VkPipelineMultisampleStateCreateInfo> SharedDataPipelineElementsInternal::AddPipelineMultisampleState(PipelineMultisampleCount multisampling, bool sampleShading, float minSampleShading)
	{
		VkPipelineMultisampleStateCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		
		switch (multisampling)
		{
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_1:
			add.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_2:
			add.rasterizationSamples = VK_SAMPLE_COUNT_2_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_4:
			add.rasterizationSamples = VK_SAMPLE_COUNT_4_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_8:
			add.rasterizationSamples = VK_SAMPLE_COUNT_8_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_16:
			add.rasterizationSamples = VK_SAMPLE_COUNT_16_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_32:
			add.rasterizationSamples = VK_SAMPLE_COUNT_32_BIT;
			break;
		case VulkanSimplified::PipelineMultisampleCount::SAMPLE_64:
			add.rasterizationSamples = VK_SAMPLE_COUNT_64_BIT;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineElementsInternal::AddPipelineMultisampleState Error: Program was given an erroneous multisample count!");
		}

		add.sampleShadingEnable = sampleShading ? VK_TRUE : VK_FALSE;
		add.minSampleShading = minSampleShading;

		return _pipelineMultiSampleStates.AddUniqueObject(add);
	}

	ListObjectID<VkPipelineDepthStencilStateCreateInfo> SharedDataPipelineElementsInternal::AddPipelineDepthState(bool depthTest, bool depthWrite, PipelineDepthCompare compare)
	{
		VkPipelineDepthStencilStateCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		add.depthTestEnable = depthTest ? VK_TRUE : VK_FALSE;
		add.depthWriteEnable = depthWrite ? VK_TRUE : VK_FALSE;

		switch (compare)
		{
		case VulkanSimplified::PipelineDepthCompare::LESS:
			add.depthCompareOp = VK_COMPARE_OP_LESS;
			break;
		case VulkanSimplified::PipelineDepthCompare::EQUAL:
			add.depthCompareOp = VK_COMPARE_OP_EQUAL;
			break;
		case VulkanSimplified::PipelineDepthCompare::LESS_OR_EQUAL:
			add.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			break;
		case VulkanSimplified::PipelineDepthCompare::GREATER:
			add.depthCompareOp = VK_COMPARE_OP_GREATER;
			break;
		case VulkanSimplified::PipelineDepthCompare::GREATER_OR_EQUAL:
			add.depthCompareOp = VK_COMPARE_OP_GREATER_OR_EQUAL;
			break;
		default:
			throw std::runtime_error("SharedDataPipelineElementsInternal::AddPipelineDepthState Error: Program was given an erroneous depth comparision setting!");
		}

		return _pipelineDepthStencilStates.AddUniqueObject(add);
	}

	ListObjectID<VkPipelineColorBlendAttachmentState> SharedDataPipelineElementsInternal::AddPipelineColorBlendAttachment(PipelineBlendSettings settings)
	{
		VkPipelineColorBlendAttachmentState add{};
		
		switch (settings)
		{
		case VulkanSimplified::PipelineBlendSettings::OFF:
			break;
		case VulkanSimplified::PipelineBlendSettings::STANDARD_NO_ALPHA:
			add.blendEnable = VK_TRUE;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_G_BIT;
			add.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			break;
		case VulkanSimplified::PipelineBlendSettings::STANDARD_ALPHA_ONE:
			add.blendEnable = VK_TRUE;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_A_BIT;
			add.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			add.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			break;
		default:
			break;
		}

		return _pipelineBlendAttachmentStates.AddUniqueObject(add);
	}

	ListObjectID<VkViewport> SharedDataPipelineElementsInternal::AddPipelineViewport(float x, float y, uint32_t width, uint32_t height, float minDepth, float maxDepth)
	{
		VkViewport add{ x, y, static_cast<float>(width), static_cast<float>(height), minDepth, maxDepth};

		return _pipelineViewports.AddUniqueObject(add);
	}

	ListObjectID<VkRect2D> SharedDataPipelineElementsInternal::AddPipelineScissor(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height)
	{
		VkRect2D add{ {static_cast<int32_t>(offsetX), static_cast<int32_t>(offsetY)}, { width, height} };

		return _pipelineScissors.AddUniqueObject(add);
	}

	ListObjectID<PipelineViewportsStateList> SharedDataPipelineElementsInternal::AddPipelineViewportState(const std::vector<std::pair<ListObjectID<VkViewport>, ListObjectID<VkRect2D>>>& viewportScissorPairs)
	{

		return _pipelineViewportStates.AddUniqueObject({ viewportScissorPairs });
	}

	bool VertexInputList::operator==(const VertexInputList& other) const noexcept
	{
		if (_bindings.size() != other._bindings.size() || _attributes.size() != other._attributes.size())	
		{
			return false;
		}
		else
		{
			for (size_t i = 0; i < _bindings.size(); ++i)
			{
				if (_bindings[i] != other._bindings[i])
					return false;
			}

			for (size_t i = 0; i < _attributes.size(); ++i)
			{
				if (_attributes[i] != other._attributes[i])
					return false;
			}

			return true;
		}
	}

	ShaderStageCreationData::ShaderStageCreationData(ShaderStageType stage, ListObjectID<ShaderContainer> mod, const char* name) : _mod(mod)
	{
		_stage = stage;
		_name = name;
		_ppadding = nullptr;
	}

	ShaderStageCreationData::~ShaderStageCreationData()
	{
	}

	bool PipelineViewportsStateList::operator==(const PipelineViewportsStateList& other) const noexcept
	{
		if (_viewportScissorPairs.size() != other._viewportScissorPairs.size())
			return false;

		for (size_t i = 0; i < _viewportScissorPairs.size(); ++i)
		{
			if (_viewportScissorPairs[i] != other._viewportScissorPairs[i])
				return false;
		}

		return true;
	}

}

bool operator==(const VkVertexInputBindingDescription& first, const VkVertexInputBindingDescription& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkVertexInputAttributeDescription& first, const VkVertexInputAttributeDescription& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkPipelineInputAssemblyStateCreateInfo& first, const VkPipelineInputAssemblyStateCreateInfo& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkPipelineRasterizationStateCreateInfo& first, const VkPipelineRasterizationStateCreateInfo& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkPipelineMultisampleStateCreateInfo& first, const VkPipelineMultisampleStateCreateInfo& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkPipelineDepthStencilStateCreateInfo& first, const VkPipelineDepthStencilStateCreateInfo& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkPipelineColorBlendAttachmentState& first, const VkPipelineColorBlendAttachmentState& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}

bool operator==(const VkViewport& first, const VkViewport& second)
{
	if (first.x != second.x)
		return false;

	if (first.y != second.y)
		return false;

	if (first.width != second.width)
		return false;

	if (first.height != second.height)
		return false;

	if (first.minDepth != second.minDepth)
		return false;

	return first.maxDepth == second.maxDepth;
}

bool operator==(const VkOffset2D& first, const VkOffset2D& second)
{
	if (first.x != second.x)
		return false;

	return first.y == second.y;
}

bool operator==(const VkExtent2D& first, const VkExtent2D& second)
{
	if (first.width != second.width)
		return false;

	return first.height == second.height;
}

bool operator==(const VkRect2D& first, const VkRect2D& second)
{
	if (first.offset != second.offset)
		return false;

	return first.extent == second.extent;
}
