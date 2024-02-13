namespace VulkanSimplified
{
	class DeviceCommandRecorderInternal
	{
		VkCommandBuffer _commandBuffer;
		void* _ppadding;

	public:
		DeviceCommandRecorderInternal(VkCommandBuffer commandBuffer);
		~DeviceCommandRecorderInternal();
	};
}