#pragma once

namespace VulkanSimplified
{
	class SharedDataSimplifierCoreInternal;
	class SharedDataPipelineElements;
	class SharedDataPipelineLayoutElements;
	class SharedDataRenderPassElements;

	class SharedDataSimplifierCore
	{
		SharedDataSimplifierCoreInternal& _internal;

	public:
		SharedDataSimplifierCore(SharedDataSimplifierCoreInternal& ref);
		~SharedDataSimplifierCore();

		SharedDataSimplifierCore(const SharedDataSimplifierCore&) noexcept = delete;
		
		SharedDataSimplifierCore& operator=(const SharedDataSimplifierCore&) noexcept = delete;

		SharedDataPipelineElements GetSharedDataPipelineElements();
		SharedDataPipelineLayoutElements GetSharedDataPipelineLayoutElements();
		SharedDataRenderPassElements GetSharedDataRenderPassElements();
	};
}


