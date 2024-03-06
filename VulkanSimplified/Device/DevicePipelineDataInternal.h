#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"

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

		VkPipelineLayout GetPipelineLayout() const;
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

		VkRenderPass GetRenderPass() const;
	};

	class AutoCleanupGraphicsPipeline
	{
		VkDevice _device;
		void* _ppadding;
		VkPipeline _pipeline;

	public:
		AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline);
		~AutoCleanupGraphicsPipeline();

		AutoCleanupGraphicsPipeline(const AutoCleanupGraphicsPipeline&) noexcept = delete;
		AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& other) noexcept;

		AutoCleanupGraphicsPipeline& operator=(const AutoCleanupGraphicsPipeline&) noexcept = delete;
		AutoCleanupGraphicsPipeline& operator=(AutoCleanupGraphicsPipeline&& other) noexcept;

		VkPipeline GetGraphicsPipeline() const;
	};

	class SharedDataSimplifierCoreInternal;
	class SharedDataPipelineLayoutElementsInternal;
	class SharedDataPipelineElementsInternal;
	class SharedDataRenderPassElementsInternal;

	class ShaderModulesSimplifierInternal;

	struct SubpassDescriptionData;

	class DevicePipelineDataInternal
	{
		const SharedDataPipelineLayoutElementsInternal& _sharedPipelineLayout;
		const SharedDataPipelineElementsInternal& _sharedPipelineData;
		const SharedDataRenderPassElementsInternal& _sharedRenderPass;
		const ShaderModulesSimplifierInternal& _deviceShaderList;

		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;
		ListTemplate<AutoCleanupPipelineLayout> _pipelineLayouts;
		ListTemplate<AutoCleanupRenderPass> _renderPasses;
		ListTemplate<AutoCleanupGraphicsPipeline> _graphicsPipelines;

	public:
		DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList, const ShaderModulesSimplifierInternal& deviceShaderList);
		~DevicePipelineDataInternal();

		DevicePipelineDataInternal(const DevicePipelineDataInternal&) noexcept = delete;

		DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList);
		ListObjectID<AutoCleanupPipelineLayout> AddPipelineLayout(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts,
			const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges);

		VkDescriptorSetLayout GetDescriptorSetLayout(ListObjectID<AutoCleanupDescriptorSetLayout> descriptorID) const;

		ListObjectID<AutoCleanupRenderPass> AddRenderPass(const std::vector<ListObjectID<VkAttachmentDescription>>& attachmentDescriptors,
			const std::vector<ListObjectID<SubpassDescriptionData>>& subpassDescriptions, const std::vector<ListObjectID<VkSubpassDependency>>& subpassDependencies);

		std::vector<ListObjectID<AutoCleanupGraphicsPipeline>> AddGraphicsPipelines(const std::vector<GraphicsPipelineCreateInfoList>& graphicsPipelinesDataLists);

		VkPipelineLayout GetPipelineLayout(ListObjectID<AutoCleanupPipelineLayout> pipelineLayoutID) const;
		VkRenderPass GetRenderPass(ListObjectID<AutoCleanupRenderPass> renderPassID) const;
		VkPipeline GetGraphicsPipeline(ListObjectID<AutoCleanupGraphicsPipeline> graphicsPipelineID) const;
	};
}