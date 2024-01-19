#include "pch.h"
#include "Include/DeviceListSimplifier.h"

#include "Include/BasicsSimplifierSharedStructs.h"
#include "DeviceListSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceListSimplifier::DeviceListSimplifier(DeviceListSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceListSimplifier::~DeviceListSimplifier()
	{
	}

	ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> DeviceListSimplifier::AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function)
	{
		return _internal.AddScoringFunction(function);
	}

}