#include "../Other/pch.h"
#include "../Include/Device/DeviceCommandRecorder.h"

#include "DeviceCommandRecorderInternal.h"

#include "../Include/Common/ListObjectID.h"

#include "../Include/Device/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{

	DeviceCommandRecorder::DeviceCommandRecorder(DeviceCommandRecorderInternal& ref) : _internal(ref)
	{
	}

	DeviceCommandRecorder::~DeviceCommandRecorder()
	{
	}

	void DeviceCommandRecorder::ResetCommandBuffer(bool releaseResources)
	{
		_internal.ResetCommandBuffer(releaseResources);
	}

	void DeviceCommandRecorder::BeginRecordingPrimaryBuffer(PrimaryBufferRecordingSettings settings)
	{
		_internal.BeginRecordingPrimaryBuffer(settings);
	}

	void DeviceCommandRecorder::EndCommandBuffer()
	{
		_internal.EndCommandBuffer();
	}

	void DeviceCommandRecorder::BindVertexInput(const std::vector<std::pair<ListObjectID<AutoCleanupShaderInputBuffer>, uint64_t>>& vertexInputs, uint32_t firstBinding)
	{
		_internal.BindVertexInput(vertexInputs, firstBinding);
	}

	void DeviceCommandRecorder::BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID)
	{
		_internal.BindGraphicsPipeline(graphicsPipelineID);
	}

	void DeviceCommandRecorder::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset)
	{
		_internal.Draw(vertexCount, instanceCount, vertexOffset, instanceOffset);
	}

	void DeviceCommandRecorder::BeginRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID, ListObjectID<AutoCleanupSwapchainFramebuffer> framebuffer, uint32_t frameID,
		uint32_t beginX, uint32_t beginY, uint32_t extendWidth, uint32_t extendHeight, const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList, bool usingSecondaryBuffers)
	{
		_internal.BeginRenderPass(renderPassID, framebuffer, frameID, beginX, beginY, extendWidth, extendHeight, clearValuesIDList, usingSecondaryBuffers);
	}

	void DeviceCommandRecorder::EndRenderPass()
	{
		_internal.EndRenderPass();
	}

	void DeviceCommandRecorder::CopyFromStagingBufferToShaderInputBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupShaderInputBuffer> shaderInputBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		_internal.CopyFromStagingBufferToShaderInputBuffer(stagingBufferID, shaderInputBufferID, copyOrders);
	}

}