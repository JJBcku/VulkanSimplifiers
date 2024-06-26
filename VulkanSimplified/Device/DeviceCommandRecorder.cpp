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

	void DeviceCommandRecorder::BindSmallIndexInput(ListObjectID<AutoCleanupSmallIndexBuffer> indexInputs, uint64_t indicesSkipped)
	{
		_internal.BindSmallIndexInput(indexInputs, indicesSkipped);
	}

	void DeviceCommandRecorder::BindBigIndexInput(ListObjectID<AutoCleanupBigIndexBuffer> indexInputs, uint64_t indicesSkipped)
	{
		_internal.BindBigIndexInput(indexInputs, indicesSkipped);
	}

	void DeviceCommandRecorder::BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID)
	{
		_internal.BindGraphicsPipeline(graphicsPipelineID);
	}

	void DeviceCommandRecorder::BindUniformBufferDescriptorSets(PipelineBindPoint bindPoint, ListObjectID<AutoCleanupPipelineLayout> pipelineLayout,
		uint32_t firstSet, const std::vector<UniformBufferDescriptorSetID>& descriptorIDs)
	{
		_internal.BindUniformBufferDescriptorSets(bindPoint, pipelineLayout, firstSet, descriptorIDs);
	}

	void DeviceCommandRecorder::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset)
	{
		_internal.Draw(vertexCount, instanceCount, vertexOffset, instanceOffset);
	}

	void DeviceCommandRecorder::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t instanceOffset)
	{
		_internal.DrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, instanceOffset);
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

	void DeviceCommandRecorder::CopyFromStagingBufferToSmallIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupSmallIndexBuffer> indexBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		_internal.CopyFromStagingBufferToSmallIndexBuffer(stagingBufferID, indexBufferID, copyOrders);
	}

	void DeviceCommandRecorder::CopyFromStagingBufferToBigIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupBigIndexBuffer> indexBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		_internal.CopyFromStagingBufferToBigIndexBuffer(stagingBufferID, indexBufferID, copyOrders);
	}

	void DeviceCommandRecorder::CopyFromStagingBufferToDescriptorSetBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupDescriptorSetsBuffer> descriptorSetBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		_internal.CopyFromStagingBufferToDescriptorSetBuffer(stagingBufferID, descriptorSetBufferID, copyOrders);
	}

}