#pragma once
#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class DeviceListSimplifierInternal;

	struct SimplifiedDeviceInfo;

	class DeviceListSimplifier
	{
		DeviceListSimplifierInternal& _internal;

	public:
		DeviceListSimplifier(DeviceListSimplifierInternal& internal);
		~DeviceListSimplifier();

		DeviceListSimplifier& operator=(const DeviceListSimplifier&) = delete;

		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore);
	};
}