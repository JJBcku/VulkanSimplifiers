#include "../pch.h"
#include "SharedDataPipelineElementsInternal.h"

//#include "../Device/ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineElementsInternal::SharedDataPipelineElementsInternal(size_t reserve) : _shaderPipelineData(reserve), _vertexInputBindingDescriptions(reserve), _vertexInputAttributeDescriptions(reserve), _vertexInputListDescriptions(reserve)
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
