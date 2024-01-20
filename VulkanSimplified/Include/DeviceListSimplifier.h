#pragma once
#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class DeviceListSimplifierInternal;

	struct SimplifiedDeviceInfo;
	struct DeviceSettings;
	class DeviceCoreSimplifierInternal;

	class DeviceListSimplifier
	{
		DeviceListSimplifierInternal& _internal;

	public:
		DeviceListSimplifier(DeviceListSimplifierInternal& internal);
		~DeviceListSimplifier();

		DeviceListSimplifier& operator=(const DeviceListSimplifier&) = delete;

		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore = std::numeric_limits<intmax_t>::lowest());
		ListObjectID<DeviceCoreSimplifierInternal> CreateDevice(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t position, DeviceSettings settings);
	};
}