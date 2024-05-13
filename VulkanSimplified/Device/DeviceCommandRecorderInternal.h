namespace VulkanSimplified
{
	class DevicePipelineDataInternal;
	class DeviceImageSimplifierInternal;
	class SharedDataPipelineElementsInternal;

	class AutoCleanupRenderPass;
	class AutoCleanupSwapchainFramebuffer;
	class AutoCleanupGraphicsPipeline;
	class AutoCleanupPipelineLayout;

	class AutoCleanupShaderInputBuffer;
	class AutoCleanupStagingBuffer;
	class AutoCleanupSmallIndexBuffer;
	class AutoCleanupBigIndexBuffer;
	class AutoCleanupDescriptorSetsBuffer;

	class DeviceDataBufferSimplifierInternal;
	class DeviceDescriptorSimplifierInternal;

	struct UniformBufferDescriptorSetID;
	struct BufferCopyOrder;

	enum class PrimaryBufferRecordingSettings : uint64_t;
	enum class PipelineBindPoint : uint64_t;

	template<class T>
	class ListObjectID;

	class DeviceCommandRecorderInternal
	{
		const DeviceImageSimplifierInternal& _imagesData;
		const DevicePipelineDataInternal& _pipelineData;
		const SharedDataPipelineElementsInternal& _sharedPipelineData;
		const DeviceDataBufferSimplifierInternal& _dataBuffersList;
		const DeviceDescriptorSimplifierInternal& _descriptorSetsList;

		VkCommandBuffer _commandBuffer;

		void CopyFromBufferToBuffer(VkBuffer sourceBuffer, VkBuffer destinationBuffer, const std::vector<BufferCopyOrder>& copyOrders);

	public:
		DeviceCommandRecorderInternal(VkCommandBuffer commandBuffer, const DeviceImageSimplifierInternal& imagesData, const DevicePipelineDataInternal& pipelineData,
			const SharedDataPipelineElementsInternal& sharedPipelineData, const DeviceDataBufferSimplifierInternal& dataBuffersList,
			const DeviceDescriptorSimplifierInternal& descriptorSetsList);
		~DeviceCommandRecorderInternal();

		DeviceCommandRecorderInternal& operator=(const DeviceCommandRecorderInternal&) noexcept = delete;

		VkCommandBuffer GetCommandBuffer() const;

		void ResetCommandBuffer(bool releaseResources);

		void BeginRecordingPrimaryBuffer(PrimaryBufferRecordingSettings settings);
		void EndCommandBuffer();

		void BindVertexInput(const std::vector<std::pair<ListObjectID<AutoCleanupShaderInputBuffer>, uint64_t>>& vertexInputs, uint32_t firstBinding);
		void BindSmallIndexInput(ListObjectID<AutoCleanupSmallIndexBuffer> indexInputs, uint64_t indicesSkipped);
		void BindBigIndexInput(ListObjectID<AutoCleanupBigIndexBuffer> indexInputs, uint64_t indicesSkipped);
		void BindGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID);

		void BindUniformBufferDescriptorSets(PipelineBindPoint bindPoint, ListObjectID<AutoCleanupPipelineLayout> pipelineLayout, uint32_t firstSet,
			const std::vector<UniformBufferDescriptorSetID>& descriptorIDs);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexOffset, uint32_t instanceOffset);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t instanceOffset);

		void BeginRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID, ListObjectID<AutoCleanupSwapchainFramebuffer> framebuffer, uint32_t frameID, uint32_t beginX,
			uint32_t beginY, uint32_t extendWidth, uint32_t extendHeight, const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList, bool secondaryBuffers);
		void EndRenderPass();

		void CopyFromStagingBufferToShaderInputBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID, ListObjectID<AutoCleanupShaderInputBuffer> destinationBufferID,
			const std::vector<BufferCopyOrder>& copyOrders);

		void CopyFromStagingBufferToSmallIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID, ListObjectID<AutoCleanupSmallIndexBuffer> destinationBufferID,
			const std::vector<BufferCopyOrder>& copyOrders);
		void CopyFromStagingBufferToBigIndexBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID, ListObjectID<AutoCleanupBigIndexBuffer> destinationBufferID,
			const std::vector<BufferCopyOrder>& copyOrders);

		void CopyFromStagingBufferToDescriptorSetBuffer(ListObjectID<AutoCleanupStagingBuffer> stagingBufferID, ListObjectID<AutoCleanupDescriptorSetsBuffer> destinationBufferID,
			const std::vector<BufferCopyOrder>& copyOrders);
	};
}