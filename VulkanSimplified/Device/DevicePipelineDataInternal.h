#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{

	class AutoCleanupDescriptorSetLayout
	{
		VkDevice _device;
		void* _ppadding;
		VkDescriptorSetLayout _descriptorSetLayout;

	public:
		AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);
		~AutoCleanupDescriptorSetLayout();

		AutoCleanupDescriptorSetLayout(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& other) noexcept;

		AutoCleanupDescriptorSetLayout& operator=(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout& operator=(AutoCleanupDescriptorSetLayout&& other) noexcept;

		VkDescriptorSetLayout GetDescriptorSetLayout() const;
	};

	class AutoCleanupPipelineLayout
	{
		VkDevice _device;
		void* _ppadding;
		VkPipelineLayout _pipelineLayout;

	public:
		AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout);
		~AutoCleanupPipelineLayout();

		AutoCleanupPipelineLayout(const AutoCleanupPipelineLayout&) noexcept = delete;
		AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& other) noexcept;

		AutoCleanupPipelineLayout& operator=(const AutoCleanupPipelineLayout&) noexcept = delete;
		AutoCleanupPipelineLayout& operator=(AutoCleanupPipelineLayout&& other) noexcept;
	};

	class AutoCleanupRenderPass
	{
		VkDevice _device;
		void* _ppadding;
		VkRenderPass _renderPass;

	public:
		AutoCleanupRenderPass(VkDevice device, VkRenderPass renderPass);
		~AutoCleanupRenderPass();

		AutoCleanupRenderPass(const AutoCleanupRenderPass&) noexcept = delete;
		AutoCleanupRenderPass(AutoCleanupRenderPass&& other) noexcept;

		AutoCleanupRenderPass& operator=(const AutoCleanupRenderPass&) noexcept = delete;
		AutoCleanupRenderPass& operator=(AutoCleanupRenderPass&& other) noexcept;
	};

	class SharedDataSimplifierCoreInternal;
	class SharedDataPipelineLayoutElementsInternal;
	class SharedDataRenderPassElementsInternal;

	struct SubpassDescriptionData;

	class DevicePipelineDataInternal
	{
		const SharedDataPipelineLayoutElementsInternal& _sharedPipelineLayout;
		const SharedDataRenderPassElementsInternal& _sharedRenderPass;

		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;
		ListTemplate<AutoCleanupPipelineLayout> _pipelineLayouts;
		ListTemplate<AutoCleanupRenderPass> _renderPasses;

	public:
		DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList);
		~DevicePipelineDataInternal();

		DevicePipelineDataInternal(const DevicePipelineDataInternal&) noexcept = delete;

		DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList);
		ListObjectID<AutoCleanupPipelineLayout> AddPipelineLayout(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts,
			const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges);

		VkDescriptorSetLayout GetDescriptorSetLayout(ListObjectID<AutoCleanupDescriptorSetLayout> descriptorID) const;

		ListObjectID<AutoCleanupRenderPass> AddRenderPass(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptors,
			const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptions, const std::vector<ListObjectID<VkSubpassDependency>>& subpassDependencies);
	};
}