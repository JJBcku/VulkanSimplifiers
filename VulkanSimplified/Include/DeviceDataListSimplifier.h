#pragma once

namespace VulkanSimplified
{
    class DeviceDataListSimplifierInternal;

    class DeviceCoreSimplifier;
    class ShaderModulesSimplifier;
    class DevicePipelineData;
    class DeviceImageSimplifier;
    class DeviceCommandBufferSimplifier;

    class DeviceDataListSimplifier
    {
        DeviceDataListSimplifierInternal& _internal;

    public:
        DeviceDataListSimplifier(DeviceDataListSimplifierInternal& ref);
        ~DeviceDataListSimplifier();

        DeviceDataListSimplifier& operator=(const DeviceDataListSimplifier&) noexcept = delete;

        DeviceCoreSimplifier GetDeviceCoreSimplifier();
        ShaderModulesSimplifier GetShaderModulesSimplifier();
        DevicePipelineData GetDevicePipelineData();
        DeviceImageSimplifier GetDeviceImageSimplifier();
        DeviceCommandBufferSimplifier GetDeviceCommandBufferSimplifier();
    };
}
