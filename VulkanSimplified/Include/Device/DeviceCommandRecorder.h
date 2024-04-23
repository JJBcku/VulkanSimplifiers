#pragma once

#include "DeviceSimplifierSharedEnums.h"

typedef uint64_t VkDeviceSize;

namespace VulkanSimplified
{
	class DeviceCommandRecorderInternal;

	class AutoCleanupRenderPass;
	class AutoCleanupSwapchainFramebuffer;
	class AutoCleanupGraphicsPipeline;

	class AutoCleanupShaderInputBuffer;

	template<class T>
	class ListObjectID;

	class DeviceCommandRecorder
	{
		DeviceCommandRecorderInternal& _internal;

	public:
		DeviceCommandRecorder(DeviceCommandRecorderInternal& ref);
		~DeviceCommandRecorder();

		DeviceCommandRecorder& operator=(const DeviceCommandRecorder&) noexcept = delete;

		void ResetCommandBuffer(bool releaseResources);

		void BeginRecordingPrimaryBuffer(PrimaryBufferRecordingSettings settings);
		void EndCommandBuffer();

		void BindVertexInput(const std::vector<std::pair<ListObjectID<AutoCleanupShaderInputBuffer>, VkDeviceSize>>& vertexInputs, uint32_t firstBinding);
		void BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset);

		void BeginRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID, ListObjectID<AutoCleanupSwapchainFramebuffer> framebuffer, uint32_t frameID, uint32_t beginX,
			uint32_t beginY, uint32_t extendWidth, uint32_t extendHeight, const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList, bool usingSecondaryBuffers);
		void EndRenderPass();
	};
}

