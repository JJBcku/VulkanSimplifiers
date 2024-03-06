#include "../Other/VulkanSimplifierListTemplate.h"

#include "../Include/Device/DeviceSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	class DevicePipelineDataInternal;
	class DeviceImageSimplifierInternal;
	class SharedDataPipelineElementsInternal;

	class AutoCleanupRenderPass;
	class AutoCleanupSwapchainFramebuffer;
	class AutoCleanupGraphicsPipeline;

	class DeviceCommandRecorderInternal
	{
		const DeviceImageSimplifierInternal& _imagesData;
		const DevicePipelineDataInternal& _pipelineData;
		const SharedDataPipelineElementsInternal& _sharedPipelineData;

		VkCommandBuffer _commandBuffer;

	public:
		DeviceCommandRecorderInternal(VkCommandBuffer commandBuffer, const DeviceImageSimplifierInternal& imagesData,
			const DevicePipelineDataInternal& pipelineData, const SharedDataPipelineElementsInternal& sharedPipelineData);
		~DeviceCommandRecorderInternal();

		DeviceCommandRecorderInternal& operator=(const DeviceCommandRecorderInternal&) noexcept = delete;

		VkCommandBuffer GetCommandBuffer() const;

		void ResetCommandBuffer(bool releaseResources);

		void BeginRecordingPrimaryBuffer(PrimaryBufferRecordingSettings settings);
		void EndCommandBuffer();

		void BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset);

		void BeginRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID, ListObjectID<AutoCleanupSwapchainFramebuffer> framebuffer, uint32_t frameID, uint32_t beginX,
			uint32_t beginY, uint32_t extendWidth, uint32_t extendHeight, const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList, bool secondaryBuffers);
		void EndRenderPass();
	};
}