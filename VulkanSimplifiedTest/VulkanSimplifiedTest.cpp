#include "stdafx.h"

#include <BasicsSimplifierSharedStructs.h>
#include <DeviceSimplifierSharedStructs.h>
#include <BasicsSimplifier.h>
#include <DeviceListSimplifier.h>
#include <VulkanSimplifierListTemplate.h>

static intmax_t GPURatingFunction(const VulkanSimplified::SimplifiedDeviceInfo& deviceInfo);

int main()
{
    using VulkanSimplified::WindowCreationData;
    using VulkanSimplified::AppData;
    using VulkanSimplified::BasicsSimplifier;
    using VulkanSimplified::DeviceSettings;

    std::cout << "Vulkan Simplified testing started!\n";

    try 
    {
        WindowCreationData windowSettings{};

        windowSettings.windowTitle = "Vulkan Simplified Test Window";
        windowSettings.windowHeight = 600;
        windowSettings.windowWidth = 800;
        windowSettings.properties = VulkanSimplified::WindowProperties::NONE;

        AppData appSettings{};
        appSettings.appTitle = "Simplified Vulkan Test App";
        appSettings.appVersion = { 0, 1, 0, 0 };
        appSettings.minVulkanVersion = { 1, 3, 0, 0 };
        appSettings.maxVulkanVersion = { 1, 3, 260, 0 };

        appSettings.engineTitle = "No engine";
        appSettings.engineVersion = { 1, 0, 0, 0 };

        std::unique_ptr<BasicsSimplifier> main = std::make_unique<BasicsSimplifier>(windowSettings, appSettings);

        auto deviceList = main->GetDeviceListSimplifier();

        auto scoringID = deviceList.AddScoringFunction(GPURatingFunction, 0);

        DeviceSettings deviceSettings;
        deviceSettings.depthUnrestricted = true;
        deviceSettings.fillRectangleNV = true;
        deviceSettings.swapchainExtension = true;

        auto device = deviceList.CreateDevice(scoringID, 0, deviceSettings);

        main.reset();
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    std::cout << "Vulkan Simplified testing successful!\n";

    return 0;
}

static intmax_t GPURatingFunction(const VulkanSimplified::SimplifiedDeviceInfo& deviceInfo)
{
    return deviceInfo.discreteGPU ? 0x10 : 0;
}
