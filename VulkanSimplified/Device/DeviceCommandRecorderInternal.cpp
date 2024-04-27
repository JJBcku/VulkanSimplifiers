#include "../Other/pch.h"
#include "DeviceCommandRecorderInternal.h"

#include "DeviceImageSimplifierInternal.h"
#include "DevicePipelineDataInternal.h"
#include "../SharedData/SharedDataPipelineElementsInternal.h"

#include "DeviceDataBufferSimplifierInternal.h"

namespace VulkanSimplified
{

	void DeviceCommandRecorderInternal::CopyFromBufferToBuffer(VkBuffer sourceBuffer, VkBuffer destinationBuffer, const std::vector<BufferCopyOrder>& copyOrders)
	{
		std::vector<VkBufferCopy> copyList;
		copyList.reserve(copyOrders.size());

		for (auto& order : copyOrders)
		{
			VkBufferCopy add{};
			add.srcOffset = order.sourceOffset;
			add.dstOffset = order.destinationOffset;
			add.size = order.dataSize;

			copyList.push_back(add);
		}

		vkCmdCopyBuffer(_commandBuffer, sourceBuffer, destinationBuffer, static_cast<uint32_t>(copyList.size()), copyList.data());
	}

	DeviceCommandRecorderInternal::DeviceCommandRecorderInternal(VkCommandBuffer commandBuffer, const DeviceImageSimplifierInternal& imagesData,
		const DevicePipelineDataInternal& pipelineData, const SharedDataPipelineElementsInternal& sharedPipelineData, const DeviceDataBufferSimplifierInternal& dataBuffersList) :
		_imagesData(imagesData), _pipelineData(pipelineData), _sharedPipelineData(sharedPipelineData), _dataBuffersList(dataBuffersList), _ppadding(nullptr),
		_commandBuffer(commandBuffer)
	{
	}

	DeviceCommandRecorderInternal::~DeviceCommandRecorderInternal()
	{
	}

	VkCommandBuffer DeviceCommandRecorderInternal::GetCommandBuffer() const
	{
		return _commandBuffer;
	}

	void DeviceCommandRecorderInternal::ResetCommandBuffer(bool releaseResources)
	{
		VkCommandBufferResetFlags flags{};

		if (releaseResources)
			flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;

		vkResetCommandBuffer(_commandBuffer, flags);
	}

	void DeviceCommandRecorderInternal::BeginRecordingPrimaryBuffer(PrimaryBufferRecordingSettings settings)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		
		switch (settings)
		{
		case VulkanSimplified::PrimaryBufferRecordingSettings::STANDARD:
			break;
		case VulkanSimplified::PrimaryBufferRecordingSettings::SINGLE_USE:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			break;
		case VulkanSimplified::PrimaryBufferRecordingSettings::MULTI_SUBMIT:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			break;
		default:
			throw std::runtime_error("DeviceCommandRecorderInternal::BeginRecordingPrimaryBuffer Error: Program was given an erroneous settings value!");
		}

		if (vkBeginCommandBuffer(_commandBuffer, &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandRecorderInternal::BeginRecordingPrimaryBuffer Error: Program failed to begin a primary command buffer!");
	}

	void DeviceCommandRecorderInternal::EndCommandBuffer()
	{
		if (vkEndCommandBuffer(_commandBuffer) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandRecorderInternal::EndCommandBuffer Error: Program failed to end a command buffer");
	}

	void DeviceCommandRecorderInternal::BindVertexInput(const std::vector<std::pair<ListObjectID<AutoCleanupShaderInputBuffer>, uint64_t>>& vertexInputs, uint32_t firstBinding)
	{
		if (vertexInputs.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandRecorderInternal::BindVertexInput Error: vertex input buffers overflow!");

		std::vector<VkBuffer> buffers;
		std::vector<uint64_t> offsets;

		buffers.reserve(vertexInputs.size());
		offsets.reserve(vertexInputs.size());

		for (auto& vertexInput : vertexInputs)
		{
			buffers.push_back(_dataBuffersList.GetShaderInputBuffer(vertexInput.first));
			offsets.push_back(vertexInput.second);
		}

		vkCmdBindVertexBuffers(_commandBuffer, firstBinding, static_cast<uint32_t>(vertexInputs.size()), buffers.data(), offsets.data());
	}

	void DeviceCommandRecorderInternal::BindSmallIndexInput(ListObjectID<AutoCleanupSmallIndexBuffer> indexInputs, uint64_t indicesSkipped)
	{
		auto buffer = _dataBuffersList.GetSmallIndexBuffer(indexInputs);

		VkDeviceSize offset = indicesSkipped * sizeof(uint16_t);

		vkCmdBindIndexBuffer(_commandBuffer, buffer, offset, VK_INDEX_TYPE_UINT16);
	}

	void DeviceCommandRecorderInternal::BindBigIndexInput(ListObjectID<AutoCleanupBigIndexBuffer> indexInputs, uint64_t indicesSkipped)
	{
		auto buffer = _dataBuffersList.GetBigIndexBuffer(indexInputs);

		VkDeviceSize offset = indicesSkipped * sizeof(uint32_t);

		vkCmdBindIndexBuffer(_commandBuffer, buffer, offset, VK_INDEX_TYPE_UINT32);
	}

	void DeviceCommandRecorderInternal::BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID)
	{
		vkCmdBindPipeline(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineData.GetGraphicsPipeline(graphicsPipelineID));
	}

	void DeviceCommandRecorderInternal::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset)
	{
		vkCmdDraw(_commandBuffer, vertexCount, instanceCount, vertexOffset, instanceOffset);
	}

	void DeviceCommandRecorderInternal::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t instanceOffset)
	{
		vkCmdDrawIndexed(_commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, instanceOffset);
	}

	void DeviceCommandRecorderInternal::BeginRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID, ListObjectID<AutoCleanupSwapchainFramebuffer> framebuffer, uint32_t frameID,
		uint32_t beginX, uint32_t beginY, uint32_t extendWidth, uint32_t extendHeight, const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList, bool secondaryBuffers)
	{
		if (clearValuesIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandRecorderInternal::BeginRenderPass Error: clear values IDs overflow!");

		VkRenderPassBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		beginInfo.renderPass = _pipelineData.GetRenderPass(renderPassID);
		beginInfo.framebuffer = _imagesData.GetSwapchainFramebuffer(framebuffer, frameID);
		beginInfo.renderArea.offset.x = static_cast<int32_t>(beginX);
		beginInfo.renderArea.offset.y = static_cast<int32_t>(beginY);
		beginInfo.renderArea.extent.width = extendWidth;
		beginInfo.renderArea.extent.height = extendHeight;

		auto clearValues = _sharedPipelineData.GetClearValues(clearValuesIDList);
		beginInfo.clearValueCount = static_cast<uint32_t>(clearValuesIDList.size());
		beginInfo.pClearValues = clearValues.data();

		VkSubpassContents subpassSettings = secondaryBuffers ? VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS : VK_SUBPASS_CONTENTS_INLINE;

		vkCmdBeginRenderPass(_commandBuffer, &beginInfo, subpassSettings);
	}

	void DeviceCommandRecorderInternal::EndRenderPass()
	{
		vkCmdEndRenderPass(_commandBuffer);
	}

	void DeviceCommandRecorderInternal::CopyFromStagingBufferToShaderInputBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupShaderInputBuffer> destinationBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		if (copyOrders.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandRecorderInternal::CopyFromStagingBuffer Error: copy orders vector overflow!");

		auto stagingBuffer = _dataBuffersList.GetStagingBuffer(stagingBufferID);
		auto destinationBuffer = _dataBuffersList.GetShaderInputBuffer(destinationBufferID);

		CopyFromBufferToBuffer(stagingBuffer, destinationBuffer, copyOrders);
	}

	void DeviceCommandRecorderInternal::CopyFromStagingBufferToSmallIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID,
		ListObjectID<AutoCleanupSmallIndexBuffer> destinationBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		if (copyOrders.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandRecorderInternal::CopyFromStagingBufferToSmallIndexBuffer Error: copy orders vector overflow!");

		auto stagingBuffer = _dataBuffersList.GetStagingBuffer(stagingBufferID);
		auto destinationBuffer = _dataBuffersList.GetSmallIndexBuffer(destinationBufferID);

		CopyFromBufferToBuffer(stagingBuffer, destinationBuffer, copyOrders);
	}

	void DeviceCommandRecorderInternal::CopyFromStagingBufferToBigIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID, ListObjectID<AutoCleanupBigIndexBuffer> destinationBufferID, const std::vector<BufferCopyOrder>& copyOrders)
	{
		if (copyOrders.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandRecorderInternal::CopyFromStagingBufferToBigIndexBuffer Error: copy orders vector overflow!");

		auto stagingBuffer = _dataBuffersList.GetStagingBuffer(stagingBufferID);
		auto destinationBuffer = _dataBuffersList.GetBigIndexBuffer(destinationBufferID);

		CopyFromBufferToBuffer(stagingBuffer, destinationBuffer, copyOrders);
	}

}