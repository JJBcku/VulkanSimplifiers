#include "../Other/pch.h"
#include "../Include/DeviceImageSimplifier.h"

#include "DeviceImageSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceImageSimplifier::DeviceImageSimplifier(DeviceImageSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceImageSimplifier::~DeviceImageSimplifier()
	{
	}

	ListObjectID<AutoCleanupSwapchainFramebuffer> DeviceImageSimplifier::AddSimpleSwapchainFramebuffer(ListObjectID<AutoCleanupRenderPass> renderPass)
	{
		return _internal.AddSimpleSwapchainFramebuffer(renderPass);
	}

}