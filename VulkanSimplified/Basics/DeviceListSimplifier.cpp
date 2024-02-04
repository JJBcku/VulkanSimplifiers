#include "../pch.h"
#include "../Include/DeviceListSimplifier.h"

#include "../Include/BasicsSimplifierSharedStructs.h"
#include "../Include/DeviceCoreSimplifier.h"
#include "DeviceListSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceListSimplifier::DeviceListSimplifier(DeviceListSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceListSimplifier::~DeviceListSimplifier()
	{
	}

	ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> DeviceListSimplifier::AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore)
	{
		return _internal.AddScoringFunction(function, minScore);
	}

	ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> DeviceListSimplifier::CreateDevice(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t position, DeviceSettings settings)
	{
		return _internal.CreateDevice(scoringFunction, position, settings);
	}

	DeviceDataListSimplifier DeviceListSimplifier::GetDeviceDataListSimplifier(const ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>>& deviceID)
	{
		return DeviceDataListSimplifier(_internal.GetDeviceDataList(deviceID));
	}

}