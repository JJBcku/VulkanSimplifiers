#include "stdafx.h"

#include <BasicsSimplifierSharedStructs.h>
#include <DeviceSimplifierSharedStructs.h>

#include <MainSimplifier.h>

#include <BasicsSimplifier.h>
#include <DeviceListSimplifier.h>
#include <SwapchainSimplifier.h>

#include <VulkanSimplifierListTemplate.h>
#include <DeviceCoreSimplifier.h>
#include <ShaderModulesSimplifier.h>

#include <SharedDataSimplifierCore.h>

#include <SharedDataPipelineLayoutElements.h>
#include <DevicePipelineData.h>

static intmax_t GPURatingFunction(const VulkanSimplified::SimplifiedDeviceInfo& deviceInfo);

std::vector<unsigned char> ReadShaderCode(std::wstring name);

int main()
{
    using VulkanSimplified::WindowCreationData;
    using VulkanSimplified::AppData;
    using VulkanSimplified::BasicsSimplifier;
    using VulkanSimplified::DeviceSettings;
    using VulkanSimplified::SharedDataSimplifierCore;
    using VulkanSimplified::MainSimplifier;

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

        std::unique_ptr<MainSimplifier> main = std::make_unique<MainSimplifier>(0x100);

        auto instanceID = main->AddInstance(windowSettings, appSettings);
        auto instance = main->GetInstanceSimplifier(instanceID);

        auto deviceList = instance.GetDeviceListSimplifier();

        auto scoringID = deviceList.AddScoringFunction(GPURatingFunction, 0);

        auto deviceAmount = deviceList.GetQualifyingDevicesAmount(scoringID);
        auto deviceInfo = deviceList.GetSimplifiedDeviceInfo(scoringID, deviceAmount - 1);

        DeviceSettings deviceSettings;
        deviceSettings.unrestrictedDepth = deviceInfo.unrestrictedDepth;
        deviceSettings.fillRectangleNV = deviceInfo.fillRectangleNV;
        deviceSettings.swapchainExtension = true;

        auto deviceID = deviceList.CreateDevice(scoringID, deviceAmount - 1, deviceSettings);
        auto deviceDataList = deviceList.GetDeviceDataListSimplifier(deviceID);
        auto device = deviceDataList.GetDeviceCoreSimplifier();

        auto shaders = deviceDataList.GetShaderModulesSimplifier();

        VulkanSimplified::SwapchainSettings swapchainSettings{};

        swapchainSettings.format = VulkanSimplified::SwapchainFormatType::TEN_BIT;
        swapchainSettings.presentMode = VulkanSimplified::SwapchainPresentMode::MAILBOX;
        swapchainSettings.imageAmount = VulkanSimplified::SwapchainImageAmount::MAX;

        auto swapchain = instance.GetSwapchainSimplifier();

        swapchain.CreateSwapchain(deviceID, swapchainSettings);

        auto vertexCode = ReadShaderCode(L"TestVertexShader.spv");
        auto fragmentCode = ReadShaderCode(L"TestFragmentShader.spv");

        auto vertexShader = shaders.CreateShaderModule(vertexCode);
        auto fragmentShader = shaders.CreateShaderModule(fragmentCode);

        auto sharedData = main->GetSharedDataCoreSimplifier();

        auto pipelineData = sharedData.GetSharedDataPipelineElements();

        auto vertexPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::VERTEX, vertexShader, "main");
        auto fragmentPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::FRAGMENT, fragmentShader, "main");

        auto testBinding = pipelineData.AddBindingDescription(0, 0, false);
        auto testAttribute = pipelineData.AddAttributeDescription(0, 0, VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT, 0);

        auto testVertexInput = pipelineData.AddVertexInputList({}, {});

        auto pipelineInputAssembly = pipelineData.AddPipelineInputAssembly(VulkanSimplified::TopologySetting::TRIANGLE);

        auto swapchainWidth = swapchain.GetSwapchainWidth();
        auto swapchainHeight = swapchain.GetSwapchainHeight();

        auto pipelineViewport = pipelineData.AddPipelineViewport(0.0f, 0.0f, swapchainWidth, swapchainHeight, 0.0f, 1.0f);
        auto pipelineScissor = pipelineData.AddPipelineScissor(0, 0, swapchainWidth, swapchainHeight);

        auto pipelineViewportState = pipelineData.AddPipelineViewportState({ {pipelineViewport, pipelineScissor} });
        auto pipelineRasterizationState = pipelineData.AddPipelineRasterizationState(VulkanSimplified::PipelinePolygonMode::FILL, VulkanSimplified::PipelineCullMode::BACK, true);

        auto pipelineMultisampling = pipelineData.AddPipelineMultisampleState(VulkanSimplified::PipelineMultisampleCount::SAMPLE_1, false, 0.0f);
        auto pipelineDepthSettings = pipelineData.AddPipelineDepthState(true, true, VulkanSimplified::PipelineDepthCompare::LESS);
        auto pipelineColorBlendAttachment = pipelineData.AddPipelineColorBlendAttachment(VulkanSimplified::PipelineBlendSettings::OFF);
        auto pipelineColorBlendState = pipelineData.AddPipelineColorBlendState({ pipelineColorBlendAttachment });

        auto pipelineLayoutData = sharedData.GetSharedDataPipelineLayoutElements();

        auto pipelineLayoutTestPushConstantRange = pipelineLayoutData.AddPushConstantRange(VulkanSimplified::VERTEX, 0, 32);
        auto pipelineSetLayoutBinding = pipelineLayoutData.AddDescriptorSetLayoutBinding(0, VulkanSimplified::PipelineLayoutDescriptorType::SAMPLER, 1, VulkanSimplified::VERTEX);

        auto devicePipelineData = deviceDataList.GetDevicePipelineData();

        auto deviceDescriptorSetLayout = devicePipelineData.AddDescriptorSetLayout({ {pipelineSetLayoutBinding} });
        auto devicePipelineLayout = devicePipelineData.AddPipelineLayout({}, {});

        auto renderPassData = sharedData.GetSharedDataRenderPassElements();

        auto renderPassAttachmentDescriptor = renderPassData.AddAttachmentDescriptionWithSwapchainsFormat(false, instanceID, VulkanSimplified::PipelineMultisampleCount::SAMPLE_1,
            VulkanSimplified::AttachmentLoadMode::CLEAR, VulkanSimplified::AttachmentStoreMode::STORE, VulkanSimplified::AttachmentLayout::IGNORED,
            VulkanSimplified::AttachmentLayout::PRESENT);

        auto renderPassAttachmentReference = renderPassData.AddAttachmentReference(0, VulkanSimplified::AttachmentLayout::COLOR);

        auto subpassDescriptor = renderPassData.AddSubpassDescriptorNoDepth(VulkanSimplified::PipelineBindPoint::GRAPHIC, {},
            { renderPassAttachmentReference }, {});

        auto subpassDependency = renderPassData.AddSubpassDependency({}, {}, VulkanSimplified::PipelineStage::TOP, VulkanSimplified::PipelineStage::BOTTOM,
            VulkanSimplified::COLOR_READ, VulkanSimplified::COLOR_WRITE);

        auto renderPass = devicePipelineData.AddRenderPass({ renderPassAttachmentDescriptor }, { subpassDescriptor }, {});

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
    if (deviceInfo.swapchainExtension)
        return deviceInfo.discreteGPU ? 0x10 : 0;
    else
        return std::numeric_limits<intmax_t>::lowest();
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