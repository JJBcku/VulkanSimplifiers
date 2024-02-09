#include "../Other/pch.h"
#include "../Include/SharedDataRenderPassElements.h"

#include "SharedDataRenderPassElementsInternal.h"

namespace VulkanSimplified
{

	SharedDataRenderPassElements::SharedDataRenderPassElements(SharedDataRenderPassElementsInternal& ref) : _internal(ref)
	{
	}

	SharedDataRenderPassElements::~SharedDataRenderPassElements()
	{
	}

	ListObjectID<VkAttachmentDescription> SharedDataRenderPassElements::AddAttachmentDescriptionWithSwapchainsFormat(bool mayAlias,
		ListObjectID<std::unique_ptr<BasicsSimplifierInternal>> instanceID, PipelineMultisampleCount sampleCount, AttachmentLoadMode loadMode, AttachmentStoreMode storeMode,
		AttachmentLayout initialLayout, AttachmentLayout finalLayout)
	{
		return _internal.AddAttachmentDescriptionWithSwapchainsFormat(mayAlias, instanceID, sampleCount, loadMode, storeMode, initialLayout, finalLayout);
	}

}