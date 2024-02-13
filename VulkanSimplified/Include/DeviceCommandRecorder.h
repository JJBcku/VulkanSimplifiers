#pragma once

namespace VulkanSimplified
{
	class DeviceCommandRecorderInternal;

	class DeviceCommandRecorder
	{
		DeviceCommandRecorderInternal& _internal;

	public:
		DeviceCommandRecorder(DeviceCommandRecorderInternal& ref);
		~DeviceCommandRecorder();

		DeviceCommandRecorder& operator=(const DeviceCommandRecorder&) noexcept = delete;
	};
}

