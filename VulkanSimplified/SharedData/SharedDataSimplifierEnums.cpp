#include "../Other/pch.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"

namespace VulkanSimplified
{
	VkPipelineStageFlags TranslatePipelineStage(PipelineStage stages)
	{
		VkPipelineStageFlags ret = 0;

		if ((stages & PipelineStage::TOP) == PipelineStage::TOP)
			ret |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

		if ((stages & PipelineStage::BOTTOM) == PipelineStage::BOTTOM)
			ret |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		if ((stages & PipelineStage::COLOR_ATTACHMENT_OUTPUT) == PipelineStage::COLOR_ATTACHMENT_OUTPUT)
			ret |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		if ((stages & PipelineStage::VERTEX_INPUT) == PipelineStage::VERTEX_INPUT)
			ret |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;

		if ((stages & PipelineStage::VERTEX_SHADER) == PipelineStage::VERTEX_SHADER)
			ret |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;

		return ret;
	}
}