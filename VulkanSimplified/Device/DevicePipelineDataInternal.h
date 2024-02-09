#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;
	class SharedDataPipelineLayoutElementsInternal;

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

	class DevicePipelineDataInternal
	{
		const SharedDataSimplifierCoreInternal& _sharedDataList;
		const SharedDataPipelineLayoutElementsInternal& _sharedPipelineLayout;

		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;
		ListTemplate<AutoCleanupPipelineLayout> _pipelineLayouts;

	public:
		DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList);
		~DevicePipelineDataInternal();

		DevicePipelineDataInternal(const DevicePipelineDataInternal&) noexcept = delete;

		DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<ListObjectID<VkDescriptorSetLayoutBinding>>& bindingsIDList);
		ListObjectID<AutoCleanupPipelineLayout> AddPipelineLayout(const std::vector<std::optional<ListObjectID<AutoCleanupDescriptorSetLayout>>>& descriptorSetLayouts,
			const std::vector<ListObjectID<VkPushConstantRange>>& pushConstantRanges);

		VkDescriptorSetLayout GetDescriptorSetLayout(ListObjectID<AutoCleanupDescriptorSetLayout> descriptorID) const;
	};
}