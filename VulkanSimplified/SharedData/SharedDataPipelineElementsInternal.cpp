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
	}

	ShaderStageCreationData::~ShaderStageCreationData()
	{
	}

}

bool operator==(const VkVertexInputBindingDescription& first, const VkVertexInputBindingDescription& second)
{
	return memcmp(&first, &second, sizeof(VkVertexInputBindingDescription)) == 0;
}

bool operator==(const VkVertexInputAttributeDescription& first, const VkVertexInputAttributeDescription& second)
{
	return memcmp(&first, &second, sizeof(VkVertexInputAttributeDescription)) == 0;
}
