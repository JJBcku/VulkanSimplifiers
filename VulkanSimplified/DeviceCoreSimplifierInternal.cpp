#include "pch.h"
#include "DeviceCoreSimplifierInternal.h"

#include "DeviceListSimplifierInternal.h"

#include "Include/ShaderModulesSimplifier.h"
#include "ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{
    VkDeviceQueueCreateInfo DeviceCoreSimplifierInternal::CreateQueueInfo(uint32_t queueFamily, const float& priority) const
    {
        VkDeviceQueueCreateInfo ret{};
        ret.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        ret.pQueuePriorities = &priority;
        ret.queueCount = 1;
        ret.pNext = nullptr;
        ret.queueFamilyIndex = queueFamily;
        ret.flags = 0;

        return ret;
    }

    void DeviceCoreSimplifierInternal::CreateDevice(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings)
    {
        VkPhysicalDeviceFeatures enabledFeatures{};
        VkPhysicalDeviceFeatures2 enabledFeatures2{};
        VkPhysicalDeviceVulkan11Features features11{};
        VkPhysicalDeviceVulkan12Features features12{};
        VkPhysicalDeviceVulkan13Features features13{};

        std::vector<VkDeviceQueueCreateInfo> queues;
        queues.reserve(3);

        auto& families = deviceInfo.queueFamilies;
        float priority = 1.0f;
        if (families.graphicsFamily.has_value())
        {
            queues.push_back(CreateQueueInfo(families.graphicsFamily.value(), priority));
        }

        if (families.computeFamily.has_value())
        {
            queues.push_back(CreateQueueInfo(families.computeFamily.value(), priority));
        }

        if (families.transferFamily.has_value())
        {
            queues.push_back(CreateQueueInfo(families.transferFamily.value(), priority));
        }

        std::vector<const char*> _requestedExtensions;
        _requestedExtensions.reserve(0x2);

        if (deviceInfo.unrestrictedDepth && deviceSettings.depthUnrestricted)
        {
            _requestedExtensions.push_back(VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME);
            _settings.depthUnrestricted = true;
        }
        else
        {
            _settings.depthUnrestricted = false;
        }

        if (deviceInfo.fillRectangleNV && deviceSettings.fillRectangleNV)
        {
            _requestedExtensions.push_back(VK_NV_FILL_RECTANGLE_EXTENSION_NAME);
            _settings.fillRectangleNV = true;
        }
        else
        {
            _settings.fillRectangleNV = false;
        }

        if (deviceInfo.swapchainExtension && deviceSettings.swapchainExtension)
        {
            _requestedExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            _settings.swapchainExtension = true;
        }
        else
        {
            _settings.swapchainExtension = false;
        }

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queues.size());
        if (!queues.empty())
            createInfo.pQueueCreateInfos = queues.data();

        createInfo.enabledExtensionCount = static_cast<uint32_t>(_requestedExtensions.size());
        if (!_requestedExtensions.empty())
            createInfo.ppEnabledExtensionNames = _requestedExtensions.data();

        if (deviceInfo.deviceApiVersion >= VK_API_VERSION_1_1)
        {
            createInfo.pNext = &enabledFeatures2;
            enabledFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
            enabledFeatures2.pNext = &features11;
            enabledFeatures2.features = enabledFeatures;
            features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;

            if (deviceInfo.deviceApiVersion >= VK_API_VERSION_1_2)
            {
                features11.pNext = &features12;
                features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

                if (deviceInfo.deviceApiVersion >= VK_API_VERSION_1_3)
                {
                    features12.pNext = &features13;
                    features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
                }
            }
        }
        else
        {
            createInfo.pEnabledFeatures = &enabledFeatures;
        }

        if (vkCreateDevice(device, &createInfo, nullptr, &_device) != VK_SUCCESS)
        {
            throw std::runtime_error("DeviceCore Error: Program failed to create a device!");
        }

        if (families.graphicsFamily.has_value())
        {
            vkGetDeviceQueue(_device, families.graphicsFamily.value(), 0, &_graphicQueue);
            _computeQueue = _graphicQueue;
            _transferQueue = _graphicQueue;
        }

        if (families.computeFamily.has_value())
        {
            vkGetDeviceQueue(_device, families.computeFamily.value(), 0, &_computeQueue);
            _transferQueue = _computeQueue;
        }

        if (families.transferFamily.has_value())
        {
            vkGetDeviceQueue(_device, families.transferFamily.value(), 0, &_transferQueue);
        }
    }

    void DeviceCoreSimplifierInternal::DestroyDevice()
    {
        if (_device != VK_NULL_HANDLE)
        {
            vkDestroyDevice(_device, nullptr);
            _device = VK_NULL_HANDLE;
        }
    }

    void DeviceCoreSimplifierInternal::CreatePointers()
    {
        _shaderSimplifier = std::make_unique<ShaderModulesSimplifierInternal>(_device);
    }

    void DeviceCoreSimplifierInternal::DestroyPointers()
    {
        if (_shaderSimplifier)
            _shaderSimplifier.reset();
    }

    DeviceCoreSimplifierInternal::DeviceCoreSimplifierInternal(VkPhysicalDevice device, const SimplifiedDeviceInfo& deviceInfo, const DeviceSettings& deviceSettings)
    {
        _device = VK_NULL_HANDLE;
        _physicalDevice = device;
        _info = deviceInfo;
        _settings = deviceSettings;

        _graphicQueue = VK_NULL_HANDLE;
        _computeQueue = VK_NULL_HANDLE;
        _transferQueue = VK_NULL_HANDLE;
        _paddingQueue = VK_NULL_HANDLE;

        CreateDevice(device, deviceInfo, deviceSettings);
        CreatePointers();
    }

    DeviceCoreSimplifierInternal::DeviceCoreSimplifierInternal(DeviceCoreSimplifierInternal&& other) noexcept
    {
        DestroyDevice();

        _device = other._device;
        other._device = VK_NULL_HANDLE;

        _physicalDevice = other._physicalDevice;
        other._physicalDevice = VK_NULL_HANDLE;

        _info = other._info;
        _settings = other._settings;

        _graphicQueue = other._graphicQueue;
        _computeQueue = other._computeQueue;
        _transferQueue = other._paddingQueue;
        _paddingQueue = VK_NULL_HANDLE;

        other._graphicQueue = VK_NULL_HANDLE;
        other._computeQueue = VK_NULL_HANDLE;
        other._transferQueue = VK_NULL_HANDLE;
        _paddingQueue = VK_NULL_HANDLE;

        _shaderSimplifier = std::move(other._shaderSimplifier);
    }

    DeviceCoreSimplifierInternal::~DeviceCoreSimplifierInternal()
    {
        DestroyPointers();
        DestroyDevice();
    }

    DeviceCoreSimplifierInternal& DeviceCoreSimplifierInternal::operator=(DeviceCoreSimplifierInternal&& other) noexcept
    {
        DestroyDevice();

        _device = other._device;
        other._device = VK_NULL_HANDLE;

        _physicalDevice = other._physicalDevice;
        other._physicalDevice = VK_NULL_HANDLE;

        _info = other._info;
        _settings = other._settings;

        _graphicQueue = other._graphicQueue;
        _computeQueue = other._computeQueue;
        _transferQueue = other._paddingQueue;

        other._graphicQueue = VK_NULL_HANDLE;
        other._computeQueue = VK_NULL_HANDLE;
        other._transferQueue = VK_NULL_HANDLE;
        _paddingQueue = VK_NULL_HANDLE;

        _shaderSimplifier = std::move(other._shaderSimplifier);

        return *this;
    }

    VkDevice DeviceCoreSimplifierInternal::GetDevice() const
    {
        return _device;
    }

    VkPhysicalDevice DeviceCoreSimplifierInternal::GetPhysicalDevice() const
    {
        return _physicalDevice;
    }

    ShaderModulesSimplifier DeviceCoreSimplifierInternal::GetShaderModulesSimplifier()
    {
        return ShaderModulesSimplifier(*_shaderSimplifier);
    }

}