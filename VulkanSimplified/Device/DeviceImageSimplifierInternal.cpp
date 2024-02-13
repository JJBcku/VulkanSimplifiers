#include "../Other/pch.h"
#include "DeviceImageSimplifierInternal.h"

#include "../Basics/SwapchainSimplifierInternal.h"
#include "DevicePipelineDataInternal.h"

namespace VulkanSimplified
{

	DeviceImageSimplifierInternal::DeviceImageSimplifierInternal(VkDevice device, const SwapchainSimplifierInternal& swapchain,
		const DevicePipelineDataInternal& pipelineData) : _swapchain(swapchain), _pipelineData(pipelineData), _device(device), _ppadding(nullptr)
	{
	}

	DeviceImageSimplifierInternal::~DeviceImageSimplifierInternal()
	{
	}

	ListObjectID<AutoCleanupSwapchainFramebuffer> DeviceImageSimplifierInternal::AddSimpleSwapchainFramebuffer(ListObjectID<AutoCleanupRenderPass> renderPass)
	{
		if (!_swapchain.DoSwapchainExist())
			throw std::runtime_error("DeviceImageSimplifierInternal::AddSimpleSwapchainFramebufferNoDepth Error: Program tried to create swapchain frame buffer before creating the swapchain!");

		std::vector<VkFramebuffer> _framebufferList;
		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;

		createInfo.width = _swapchain.GetSwapchainWidth();
		createInfo.height = _swapchain.GetSwapchainHeight();
		createInfo.layers = 1;

		createInfo.renderPass = _pipelineData.GetRenderPass(renderPass);
		createInfo.attachmentCount = 1;

		auto swapchainImageViews = _swapchain.GetSwapchainImageViewList();
		_framebufferList.resize(swapchainImageViews.size(), VK_NULL_HANDLE);

		for (size_t i = 0; i < swapchainImageViews.size(); ++i)
		{
			createInfo.pAttachments = &swapchainImageViews[i];

			if (vkCreateFramebuffer(_device, &createInfo, nullptr, &_framebufferList[i]) != VK_SUCCESS)
				throw std::runtime_error("DeviceImageSimplifierInternal::AddSimpleSwapchainFramebufferNoDepth Error: Program failed to create a framebuffer!");
		}

		return _swapchainFramebuffers.AddObject(AutoCleanupSwapchainFramebuffer(_device, std::move(_framebufferList)));
	}

	AutoCleanupFramebuffer::AutoCleanupFramebuffer(VkDevice device, VkFramebuffer framebuffer) : _device(device), _ppadding(nullptr), _framebuffer(framebuffer)
	{
	}

	AutoCleanupFramebuffer::~AutoCleanupFramebuffer()
	{
		if (_framebuffer != VK_NULL_HANDLE)
		{
			vkDestroyFramebuffer(_device, _framebuffer, nullptr);
		}
	}

	AutoCleanupFramebuffer::AutoCleanupFramebuffer(AutoCleanupFramebuffer&& other) noexcept : _device(other._device), _ppadding(nullptr), _framebuffer(other._framebuffer)
	{
		other._device = VK_NULL_HANDLE;
		other._framebuffer = VK_NULL_HANDLE;
	}

	AutoCleanupFramebuffer& AutoCleanupFramebuffer::operator=(AutoCleanupFramebuffer&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_framebuffer = other._framebuffer;

		other._device = VK_NULL_HANDLE;
		other._framebuffer = VK_NULL_HANDLE;

		return *this;
	}

	VkFramebuffer AutoCleanupFramebuffer::GetFramebuffer() const
	{
		return _framebuffer;
	}

	AutoCleanupSwapchainFramebuffer::AutoCleanupSwapchainFramebuffer(VkDevice device, const std::vector<VkFramebuffer>& framebuffers) : _device(device), _framebuffers(framebuffers)
	{
	}

	AutoCleanupSwapchainFramebuffer::AutoCleanupSwapchainFramebuffer(VkDevice device, std::vector<VkFramebuffer>&& framebuffers) : _device(device), _framebuffers(std::move(framebuffers))
	{
	}

	AutoCleanupSwapchainFramebuffer::~AutoCleanupSwapchainFramebuffer()
	{
		for (auto& framebuffer : _framebuffers)
		{
			if (framebuffer != VK_NULL_HANDLE)
				vkDestroyFramebuffer(_device, framebuffer, nullptr);
		}
	}

	AutoCleanupSwapchainFramebuffer::AutoCleanupSwapchainFramebuffer(AutoCleanupSwapchainFramebuffer&& other) noexcept : _device(other._device),
		_framebuffers(std::move(other._framebuffers))
	{
		other._device = VK_NULL_HANDLE;
	}

	AutoCleanupSwapchainFramebuffer& AutoCleanupSwapchainFramebuffer::operator=(AutoCleanupSwapchainFramebuffer&& other) noexcept
	{
		_device = other._device;
		other._device = VK_NULL_HANDLE;

		_framebuffers = std::move(other._framebuffers);

		return *this;
	}

	VkFramebuffer AutoCleanupSwapchainFramebuffer::GetFramebuffer(size_t index) const
	{
		if (_framebuffers.size() <= index)
			throw std::runtime_error("AutoCleanupSwapchainFramebuffer::GetFramebuffer Error: Program tried to read data outside of vector memory!");

		return _framebuffers[index];
	}

}