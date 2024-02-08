#include "../Include/VulkanSimplifierListTemplate.h"
#include "../Include/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;
	class SharedDataPipelineLayoutElementsInternal;

	class AutoCleanupDescriptorSetLayout
	{
		VkDevice _device;
		VkDescriptorSetLayout _descriptorSetLayout;

	public:
		AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);
		~AutoCleanupDescriptorSetLayout();

		AutoCleanupDescriptorSetLayout(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& other) noexcept;

		AutoCleanupDescriptorSetLayout& operator=(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout& operator=(AutoCleanupDescriptorSetLayout&& other) noexcept;
	};

	class DevicePipelineDataInternal
	{
		const SharedDataSimplifierCoreInternal& _sharedDataList;
		const SharedDataPipelineLayoutElementsInternal& _sharedPipelineLayout;

		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;

	public:
		DevicePipelineDataInternal(VkDevice device, const SharedDataSimplifierCoreInternal& sharedDataList);
		~DevicePipelineDataInternal();

		DevicePipelineDataInternal(const DevicePipelineDataInternal&) noexcept = delete;

		DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

		ListObjectID<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(const std::vector<BindingIDsOptional>& bindingsIDList);
	};
}