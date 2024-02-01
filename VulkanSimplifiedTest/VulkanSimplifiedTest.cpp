#include "stdafx.h"

#include <BasicsSimplifierSharedStructs.h>
#include <DeviceSimplifierSharedStructs.h>

#include <BasicsSimplifier.h>
#include <DeviceListSimplifier.h>
#include <SwapchainSimplifier.h>

#include <VulkanSimplifierListTemplate.h>
#include <DeviceCoreSimplifier.h>
#include <ShaderModulesSimplifier.h>

#include <SharedDataSimplifierCore.h>

static intmax_t GPURatingFunction(const VulkanSimplified::SimplifiedDeviceInfo& deviceInfo);

std::vector<unsigned char> ReadShaderCode(std::wstring name);

int main()
{
    using VulkanSimplified::WindowCreationData;
    using VulkanSimplified::AppData;
    using VulkanSimplified::BasicsSimplifier;
    using VulkanSimplified::DeviceSettings;
    using VulkanSimplified::SharedDataSimplifierCore;

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
        appSettings.appVersion = { 0, 2, 0, 0 };
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

        auto deviceID = deviceList.CreateDevice(scoringID, 0, deviceSettings);
        auto deviceDataList = deviceList.GetDeviceDataListSimplifier(deviceID);
        auto device = deviceDataList.GetDeviceCoreSimplifier();

        auto shaders = deviceDataList.GetShaderModulesSimplifier();

        VulkanSimplified::SwapchainSettings swapchainSettings{};

        swapchainSettings.format = VulkanSimplified::SwapchainFormatType::TEN_BIT;
        swapchainSettings.presentMode = VulkanSimplified::SwapchainPresentMode::MAILBOX;
        swapchainSettings.imageAmount = VulkanSimplified::SwapchainImageAmount::MAX;

        auto swapchain = main->GetSwapchainSimplifier();

        swapchain.CreateSwapchain(deviceID, swapchainSettings);

        auto vertexCode = ReadShaderCode(L"TestVertexShader.spv");
        auto fragmentCode = ReadShaderCode(L"TestFragmentShader.spv");

        auto vertexShader = shaders.CreateShaderModule(vertexCode);
        auto fragmentShader = shaders.CreateShaderModule(fragmentCode);

        SharedDataSimplifierCore sharedData(0x100);

        auto pipelineData = sharedData.GetSharedDataPipelineElements();

        auto vertexPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::VERTEX, vertexShader, "main");
        auto fragmentPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::FRAGMENT, fragmentShader, "main");

        auto testBinding = pipelineData.AddBindingDescription(0, 0, false);
        auto testAttribute = pipelineData.AddAttributeDescription(0, 0, VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT, 0);

        auto testVertexInput = pipelineData.AddVertexInputList({}, {});

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

std::vector<unsigned char> ReadShaderCode(std::wstring name)
{
    std::vector<unsigned char> ret;

    std::ifstream file;

    file.open(name, std::ios_base::binary | std::ios_base::ate | std::ios_base::in);

    if (!file.is_open())
        throw std::runtime_error("Program failed to open a shader file!");

    file.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);

    auto size = file.tellg();

    ret.resize(static_cast<size_t>(size));

    file.seekg(0);

    file.read(reinterpret_cast<char*>(ret.data()), static_cast<std::streamsize>(size));

    file.close();

    return ret;
}