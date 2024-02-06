#include "../Other/pch.h"
#include "SharedDataPipelineLayoutElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataPipelineLayoutElementsInternal::SharedDataPipelineLayoutElementsInternal(size_t reserve) : _pushConstants(reserve)
	{
	}

	SharedDataPipelineLayoutElementsInternal::~SharedDataPipelineLayoutElementsInternal()
	{
	}

	ListObjectID<VkPushConstantRange> SharedDataPipelineLayoutElementsInternal::AddPushConstantRange(ShaderStageFlags shaderStages, uint32_t offset, uint32_t size)
	{
		VkPushConstantRange add{};

		if ((offset & 3) != 0)
			throw std::runtime_error("SharedDataPipelineLayoutElements::AddPushConstantRange: Program was given an offset which is not a multiple of 4!");

		if ((size & 3) != 0)
			throw std::runtime_error("SharedDataPipelineLayoutElements::AddPushConstantRange: Program was given a size which is not a multiple of 4!");

		if ((shaderStages & ShaderStageFlags::VERTEX) == ShaderStageFlags::VERTEX)
			add.stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;

		if ((shaderStages & ShaderStageFlags::FRAGMENT) == ShaderStageFlags::FRAGMENT)
			add.stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;

		add.offset = offset;
		add.size = size;

		return _pushConstants.AddUniqueObject(add);
	}

}

bool operator==(const VkPushConstantRange& first, const VkPushConstantRange& second)
{
	return memcmp(&first, &second, sizeof(first)) == 0;
}
