#pragma once

#include "VulkanSimplifierListTemplate.h"
#include "SharedDataSimplifierEnums.h"

struct VkAttachmentDescription;

namespace VulkanSimplified
{
	class BasicsSimplifierInternal;
	class SharedDataRenderPassElementsInternal;

	class SharedDataRenderPassElements
	{
		SharedDataRenderPassElementsInternal& _internal;

	public:
		SharedDataRenderPassElements(SharedDataRenderPassElementsInternal& ref);
		~SharedDataRenderPassElements();

		SharedDataRenderPassElements& operator=(const SharedDataRenderPassElements&) noexcept = delete;

		ListObjectID<VkAttachmentDescription> AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias, ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount,
			AttachmentLoadMode loadMode, AttachmentStoreMode storeMode, AttachmentLayout initialLayout, AttachmentLayout finalLayout);
	};
}
