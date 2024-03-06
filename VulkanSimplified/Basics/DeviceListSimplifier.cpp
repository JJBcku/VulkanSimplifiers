#include "../Other/pch.h"
#include "../Include/Basics/DeviceListSimplifier.h"

#include "../Include/Basics/BasicsSimplifierSharedStructs.h"
#include "../Include/Device/DeviceCoreSimplifier.h"
#include "../Device/DeviceDataListSimplifierInternal.h"
#include "DeviceListSimplifierInternal.h"

#include "../Include/Common/ListObjectID.h"
#include "../Include/Device/DeviceDataListSimplifier.h"

namespace VulkanSimplified
{
	DeviceListSimplifier::DeviceListSimplifier(DeviceListSimplifierInternal& ref) : _internal(ref), _ppadding(nullptr)
	{
	}

	DeviceListSimplifier::~DeviceListSimplifier()
	{
	}

	SimplifiedDeviceInfo DeviceListSimplifier::GetSimplifiedDeviceInfo(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID, size_t position)
	{
		return _internal.GetSimplifiedDeviceInfo(scoringFunctionID, position);
	}

	size_t DeviceListSimplifier::GetQualifyingDevicesAmount(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID)
	{
		return _internal.GetQualifyingDevicesAmount(scoringFunctionID);
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