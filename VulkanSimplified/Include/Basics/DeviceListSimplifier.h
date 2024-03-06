#pragma once

namespace VulkanSimplified
{
	template<class T>
	class ListObjectID;

	class DeviceListSimplifierInternal;

	struct SimplifiedDeviceInfo;
	struct DeviceSettings;

	class DeviceCoreSimplifierInternal;
	class DeviceCoreSimplifier;
	class DeviceDataListSimplifier;
	class DeviceDataListSimplifierInternal;

	class DeviceListSimplifier
	{
		DeviceListSimplifierInternal& _internal;
		void* _ppadding;

	public:
		DeviceListSimplifier(DeviceListSimplifierInternal& internal);
		~DeviceListSimplifier();

		DeviceListSimplifier& operator=(const DeviceListSimplifier&) = delete;

		SimplifiedDeviceInfo GetSimplifiedDeviceInfo(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID, size_t position);

		size_t GetQualifyingDevicesAmount(ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> scoringFunctionID);

		ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>> AddScoringFunction(std::function<intmax_t(const SimplifiedDeviceInfo&)> function, intmax_t minScore = std::numeric_limits<intmax_t>::lowest());
		ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>> CreateDevice(const ListObjectID<std::function<intmax_t(const SimplifiedDeviceInfo&)>>& scoringFunction, size_t position, DeviceSettings settings);

		DeviceDataListSimplifier GetDeviceDataListSimplifier(const ListObjectID<std::unique_ptr<DeviceDataListSimplifierInternal>>& deviceID);
	};
}