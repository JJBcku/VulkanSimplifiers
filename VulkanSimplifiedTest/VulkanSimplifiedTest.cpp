#include "stdafx.h"

#include <Basics/BasicsSimplifierSharedStructs.h>
#include <Device/DeviceSimplifierSharedStructs.h>

#include <Common/MainSimplifier.h>

#include <Basics/BasicsSimplifier.h>
#include <Basics/DeviceListSimplifier.h>
#include <Basics/SwapchainSimplifier.h>
#include <Basics/SwapchainSimplifierEnums.h>
#include <Basics/SwapchainSimplifierStructs.h>
#include <Basics/WindowSimplifier.h>

#include <Device/DeviceDataListSimplifier.h>
#include <Device/DeviceCoreSimplifier.h>
#include <Device/ShaderModulesSimplifier.h>

#include <SharedData/SharedDataSimplifierCore.h>

#include <SharedData/SharedDataPipelineLayoutElements.h>
#include <SharedData/SharedDataPipelineElements.h>
#include <SharedData/SharedDataRenderPassElements.h>
#include <Device/DevicePipelineData.h>

#include <Device/DeviceImageSimplifier.h>
#include <Device/DeviceCommandBufferSimplifier.h>

#include <Device/DeviceSynchronizationSimplifier.h>

#include <Common/ListObjectID.h>

#include <Device/DeviceMemorySimplifier.h>

static intmax_t GPURatingFunction(const VulkanSimplified::SimplifiedDeviceInfo& deviceInfo);

std::vector<unsigned char> ReadShaderCode(std::wstring name);

struct Vertex
{
    glm::vec4 Color;
    glm::vec2 Position;
};

std::vector<Vertex> _vertexes = {
    {{ 1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, -0.5f}},
    {{ 0.0f, 1.0f, 0.0f, 1.0f}, {0.5f, 0.5f}},
    {{ 0.0f, 0.0f, 1.0f, 1.0f}, {-0.5f, 0.5f}}
};

int main()
{
    using VulkanSimplified::WindowCreationData;
    using VulkanSimplified::AppData;
    using VulkanSimplified::BasicsSimplifier;
    using VulkanSimplified::DeviceSettings;
    using VulkanSimplified::SharedDataSimplifierCore;
    using VulkanSimplified::MainSimplifier;
    using VulkanSimplified::ListObjectID;

    std::cout << "Vulkan Simplified testing started!\n";

    try 
    {
        WindowCreationData windowSettings{};

        windowSettings.windowTitle = "Vulkan Simplified Test Window";
        windowSettings.windowHeight = 600;
        windowSettings.windowWidth = 800;
        windowSettings.properties = VulkanSimplified::WindowProperties::RESIZABLE;

        AppData appSettings{};
        appSettings.appTitle = "Simplified Vulkan Test App";
        appSettings.appVersion = { 0, 2, 0, 0 };
        appSettings.minVulkanVersion = { 1, 3, 0, 0 };
        appSettings.maxVulkanVersion = { 1, 3, 260, 0 };

        appSettings.engineTitle = "No engine";
        appSettings.engineVersion = { 1, 0, 0, 0 };

        std::unique_ptr<MainSimplifier> main = std::make_unique<MainSimplifier>(0x100, windowSettings, appSettings);

        auto instance = main->GetInstanceSimplifier();

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

        auto window = instance.GetWindowSimplifier();

        VulkanSimplified::SwapchainSettings swapchainSettings{};

        swapchainSettings.format = VulkanSimplified::SwapchainFormatType::TEN_BIT;
        swapchainSettings.presentMode = VulkanSimplified::SwapchainPresentMode::FIFO;
        swapchainSettings.imageAmount = VulkanSimplified::SwapchainImageAmount::MAX;

        auto swapchain = instance.GetSwapchainSimplifier();

        swapchain.CreateSwapchain(deviceID, swapchainSettings);

        auto vertexCode = ReadShaderCode(L"TestVertexShader.spv");
        auto fragmentCode = ReadShaderCode(L"TestFragmentShader.spv");

        auto vertexShader = shaders.CreateShaderModule(vertexCode);
        auto fragmentShader = shaders.CreateShaderModule(fragmentCode);

        auto sharedData = main->GetSharedDataCoreSimplifier();

        auto pipelineData = sharedData.GetSharedDataPipelineElements();

        auto vertexPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::VERTEX, "main");
        auto fragmentPipelineData = pipelineData.AddShaderPipelineData(VulkanSimplified::ShaderStageType::FRAGMENT, "main");

        auto vertexBindingDescription = pipelineData.AddBindingDescription(0, 0, false);
        auto vertexColorAttributeDescription = pipelineData.AddAttributeDescription(0, 0, VulkanSimplified::VertexAttributeFormats::VEC4_FLOAT, 0);
        auto vertexPositionAttributeDescription = pipelineData.AddAttributeDescription(1, 0, VulkanSimplified::VertexAttributeFormats::VEC2_FLOAT, sizeof(glm::vec4));

        auto testVertexInput = pipelineData.AddVertexInputList({ vertexBindingDescription }, { vertexColorAttributeDescription, vertexPositionAttributeDescription });

        auto pipelineInputAssembly = pipelineData.AddPipelineInputAssembly(VulkanSimplified::TopologySetting::TRIANGLE);

        auto swapchainWidth = swapchain.GetSwapchainWidth();
        auto swapchainHeight = swapchain.GetSwapchainHeight();

        std::vector<ListObjectID<VkViewport>> pipelineViewport;
        pipelineViewport.push_back(pipelineData.AddPipelineViewport(0.0f, 0.0f, swapchainWidth, swapchainHeight, 0.0f, 1.0f));
        std::vector<ListObjectID<VkRect2D>> pipelineScissor;
        pipelineScissor.push_back(pipelineData.AddPipelineScissor(0, 0, swapchainWidth, swapchainHeight));

        std::vector<ListObjectID<VulkanSimplified::PipelineViewportsStateList>> pipelineViewportStatesList;

        pipelineViewportStatesList.push_back(pipelineData.AddPipelineViewportState({ {pipelineViewport[0], pipelineScissor[0]} }));
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

        auto renderPassAttachmentDescriptor = renderPassData.AddAttachmentDescriptionWithSwapchainsFormat(false, VulkanSimplified::PipelineMultisampleCount::SAMPLE_1,
            VulkanSimplified::AttachmentLoadMode::CLEAR, VulkanSimplified::AttachmentStoreMode::STORE, VulkanSimplified::AttachmentLayout::IGNORED,
            VulkanSimplified::AttachmentLayout::PRESENT);

        auto renderPassAttachmentReference = renderPassData.AddAttachmentReference(0, VulkanSimplified::AttachmentLayout::COLOR);

        auto subpassDescriptor = renderPassData.AddSubpassDescriptorNoDepth(VulkanSimplified::PipelineBindPoint::GRAPHIC, {},
            { renderPassAttachmentReference }, {});

        auto subpassDependency = renderPassData.AddSubpassDependency({}, 0, VulkanSimplified::PipelineStage::COLOR_ATTACHMENT_OUTPUT,
            VulkanSimplified::PipelineStage::COLOR_ATTACHMENT_OUTPUT, VulkanSimplified::NO_ACCESS, VulkanSimplified::COLOR_WRITE);

        auto renderPass = devicePipelineData.AddRenderPass({ renderPassAttachmentDescriptor }, { subpassDescriptor }, { subpassDependency });

        VulkanSimplified::GraphicsPipelineCreateInfoList createInfo{};

        createInfo._shaderStagesDataList.reserve(2);
        createInfo._shaderStagesDataList.push_back({vertexShader, vertexPipelineData});
        createInfo._shaderStagesDataList.push_back({fragmentShader, fragmentPipelineData});

        createInfo._vertexInput = testVertexInput;
        createInfo._inputAssembly = pipelineInputAssembly;
        createInfo._viewportState = pipelineViewportStatesList[0];
        createInfo._rasterizationState = pipelineRasterizationState;
        createInfo._multisamplingState = pipelineMultisampling;
        createInfo._colorBlendState = pipelineColorBlendState;
        createInfo._pipelineLayout = devicePipelineLayout;
        createInfo._renderPass = renderPass;
        createInfo._subpass = 0;
        createInfo._basePipelineID._idType = VulkanSimplified::BasePipelineIDType::NONE;
        createInfo._allowDerivatives = false;

        auto pipelineList = devicePipelineData.AddGraphicsPipelines({ createInfo });

        auto imageSimplifier = deviceDataList.GetDeviceImageSimplifier();

        auto swapchainFramebuffers = imageSimplifier.AddSimpleSwapchainFramebuffer(renderPass);

        auto commandBufferList = deviceDataList.GetDeviceCommandBufferSimplifier();

        auto commandPool = commandBufferList.AddCommandPool(VulkanSimplified::QueueFamilyType::GRAPHICS, true, true);

        uint32_t frameAmount = swapchain.GetSwapchainImagesAmount();

        std::vector<ListObjectID<std::unique_ptr<VulkanSimplified::DeviceCommandRecorderInternal>>> commandBufferIDList;
        std::vector<VulkanSimplified::DeviceCommandRecorder> commandRecorderList;

        commandBufferIDList.reserve(frameAmount);
        commandRecorderList.reserve(frameAmount);

        for (uint32_t i = 0; i < frameAmount; ++i)
        {
            commandBufferIDList.push_back(commandBufferList.AddPrimaryCommandBuffer(commandPool));
            commandRecorderList.push_back(commandBufferList.GetPrimaryDeviceCommandBuffersRecorder(commandBufferIDList[i]));
        }

        auto colorClearValue = pipelineData.AddClearColorValue(0.0f, 0.0f, 0.0f, 1.0f);

        auto deviceSynchronization = deviceDataList.GetDeviceSynchronizationSimplifier();

        auto deviceMemory = deviceDataList.GetDeviceMemorySimplifier();

        std::vector<ListObjectID<VulkanSimplified::AutoCleanupSemaphore>> imageAvailableSemaphoresList;
        std::vector<ListObjectID<VulkanSimplified::AutoCleanupSemaphore>> renderFinishedSemaphoresList;
        std::vector<ListObjectID<VulkanSimplified::AutoCleanupFence>> inFlightFencesList;

        imageAvailableSemaphoresList.reserve(frameAmount);
        renderFinishedSemaphoresList.reserve(frameAmount);
        inFlightFencesList.reserve(frameAmount);

        VulkanSimplified::SharedDeviceMemoryID vectorMemory = deviceMemory.AddSharedMemory(0x1000, true, false);

        for (uint32_t i = 0; i < frameAmount; ++i)
        {
            imageAvailableSemaphoresList.push_back(deviceSynchronization.AddSemaphore());
            renderFinishedSemaphoresList.push_back(deviceSynchronization.AddSemaphore());
            inFlightFencesList.push_back(deviceSynchronization.AddFence(true));
        }

        uint32_t imageAmount = 0;

        uint32_t currentImage = 0;
        uint32_t currentSynchro = 0;

        size_t pipelineID = 0;

        bool redoSwapchain = false;

        while(!window.GetQuit())
        {
            window.HandleEvents();

            if (window.GetPaused())
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ms);
                continue;
            }

            deviceSynchronization.WaitForFences({ inFlightFencesList[currentSynchro] }, 1000, false);
            deviceSynchronization.ResetFences({ inFlightFencesList[currentSynchro] });

            redoSwapchain = redoSwapchain || window.GetResized();

            if (redoSwapchain)
            {
                device.WaitForIdleness();
                swapchain.ReCreateSwapchain(deviceID, swapchainSettings);

                swapchainWidth = swapchain.GetSwapchainWidth();
                swapchainHeight = swapchain.GetSwapchainHeight();

                swapchainFramebuffers = imageSimplifier.AddSimpleSwapchainFramebuffer(renderPass);

                auto newViewport = pipelineData.AddPipelineViewport(0, 0, swapchainWidth, swapchainHeight, 0.0f, 1.0f);
                auto newScissors = pipelineData.AddPipelineScissor(0, 0, swapchainWidth, swapchainHeight);

                auto scissorFind = std::find(pipelineScissor.begin(), pipelineScissor.end(), newScissors);

                if (scissorFind != pipelineScissor.cend())
                {
                    pipelineID = static_cast<size_t>(std::distance(pipelineScissor.begin(), scissorFind));
                }
                else
                {
                    pipelineID = pipelineScissor.size();

                    pipelineViewport.push_back(newViewport);
                    pipelineScissor.push_back(newScissors);

                    pipelineViewportStatesList.push_back(pipelineData.AddPipelineViewportState({ {pipelineViewport[pipelineID], pipelineScissor[pipelineID]} }));

                    createInfo._viewportState = pipelineViewportStatesList[pipelineID];

                    auto newPipelines = devicePipelineData.AddGraphicsPipelines({ createInfo });

                    pipelineList.push_back(newPipelines[0]);
                }

                redoSwapchain = false;
            }

            auto nextImage = swapchain.AcquireNextImage(std::numeric_limits<uint64_t>::max(), imageAvailableSemaphoresList[currentSynchro], {});
            currentImage = nextImage.first;
            redoSwapchain = !nextImage.second;

            commandRecorderList[currentImage].ResetCommandBuffer(false);

            commandRecorderList[currentImage].BeginRecordingPrimaryBuffer(VulkanSimplified::PrimaryBufferRecordingSettings::SINGLE_USE);

            commandRecorderList[currentImage].BeginRenderPass(renderPass, swapchainFramebuffers, currentImage, 0, 0, swapchainWidth, swapchainHeight, { colorClearValue }, false);
            
            commandRecorderList[currentImage].BindGraphicsPipeline(pipelineList[pipelineID]);
            commandRecorderList[currentImage].Draw(3, 1, 0, 0);

            commandRecorderList[currentImage].EndRenderPass();

            commandRecorderList[currentImage].EndCommandBuffer();

            VulkanSimplified::QueueSubmitObject submitObject;
            submitObject._commandBuffer = { commandBufferIDList[currentImage] };
            submitObject._waitSemaphores = { {VulkanSimplified::PipelineStage::COLOR_ATTACHMENT_OUTPUT, imageAvailableSemaphoresList[currentSynchro]} };
            submitObject._signalSemaphores = { renderFinishedSemaphoresList[currentSynchro] };

            commandBufferList.SubmitToQueue(VulkanSimplified::QueueFamilyType::GRAPHICS, { submitObject }, { inFlightFencesList[currentSynchro] });

            bool result = swapchain.PresentImage({ renderFinishedSemaphoresList[currentSynchro] }, currentImage);

            redoSwapchain = !result || redoSwapchain;

            imageAmount++;
            currentSynchro++;

            if (currentSynchro >= frameAmount)
                currentSynchro = 0;
        }

        device.WaitForIdleness();

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