#pragma once
#include "../Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class SwapchainSimplifierInternal;
	class DevicePipelineDataInternal;

	class AutoCleanupRenderPass;

	class AutoCleanupFramebuffer
	{
		VkDevice _device;
		void* _ppadding;
		VkFramebuffer _framebuffer;

	public:
		AutoCleanupFramebuffer(VkDevice device, VkFramebuffer framebuffer);
		~AutoCleanupFramebuffer();

		AutoCleanupFramebuffer(const AutoCleanupFramebuffer&) noexcept = delete;
		AutoCleanupFramebuffer(AutoCleanupFramebuffer&& other) noexcept;

		AutoCleanupFramebuffer& operator=(const AutoCleanupFramebuffer&) noexcept = delete;
		AutoCleanupFramebuffer& operator=(AutoCleanupFramebuffer&& other) noexcept;

		VkFramebuffer GetFramebuffer() const;
	};

	class AutoCleanupSwapchainFramebuffer
	{
		VkDevice _device;
		std::vector<VkFramebuffer> _framebuffers;

	public:
		AutoCleanupSwapchainFramebuffer(VkDevice device, const std::vector<VkFramebuffer>& framebuffers);
		AutoCleanupSwapchainFramebuffer(VkDevice device, std::vector<VkFramebuffer>&& framebuffers);
		~AutoCleanupSwapchainFramebuffer();

		AutoCleanupSwapchainFramebuffer(const AutoCleanupSwapchainFramebuffer&) noexcept = delete;
		AutoCleanupSwapchainFramebuffer(AutoCleanupSwapchainFramebuffer&& other) noexcept;

		AutoCleanupSwapchainFramebuffer& operator=(const AutoCleanupSwapchainFramebuffer&) noexcept = delete;
		AutoCleanupSwapchainFramebuffer& operator=(AutoCleanupSwapchainFramebuffer&& other) noexcept;

		VkFramebuffer GetFramebuffer(size_t index) const;
	};

	class DeviceImageSimplifierInternal
	{
		const SwapchainSimplifierInternal& _swapchain;
		const DevicePipelineDataInternal& _pipelineData;

		VkDevice _device;
		void* _ppadding;
		ListTemplate<AutoCleanupSwapchainFramebuffer> _swapchainFramebuffers;

	public:
		DeviceImageSimplifierInternal(VkDevice device, const SwapchainSimplifierInternal& swapchain, const DevicePipelineDataInternal& pipelineData);
		~DeviceImageSimplifierInternal();

		DeviceImageSimplifierInternal(const DeviceImageSimplifierInternal&) noexcept = delete;

		DeviceImageSimplifierInternal& operator=(const DeviceImageSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupSwapchainFramebuffer> AddSimpleSwapchainFramebuffer(ListObjectID<AutoCleanupRenderPass> renderPass);

		VkFramebuffer GetSwapchainFramebuffer(ListObjectID<AutoCleanupSwapchainFramebuffer> framebufferID, uint32_t frameID) const;

		void DestroySwapchainFramebuffers();
	};
}