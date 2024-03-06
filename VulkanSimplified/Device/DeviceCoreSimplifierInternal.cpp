#include "../Other/pch.h"
#include "DeviceCoreSimplifierInternal.h"

#include "../Basics/DeviceListSimplifierInternal.h"

#include "../Include/Device/ShaderModulesSimplifier.h"
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

        if (deviceInfo.unrestrictedDepth && deviceSettings.unrestrictedDepth)
        {
            _requestedExtensions.push_back(VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME);
            _settings.unrestrictedDepth = true;
        }
        else
        {
            if (!deviceInfo.unrestrictedDepth && deviceSettings.unrestrictedDepth)
                throw std::runtime_error("DeviceCoreSimplifierInternal::CreateDevice Error: Program tried to create logical device with unrestricted depth enabled on an uncompatible physical device!");

            _settings.unrestrictedDepth = false;
        }

        if (deviceInfo.fillRectangleNV && deviceSettings.fillRectangleNV)
        {
            _requestedExtensions.push_back(VK_NV_FILL_RECTANGLE_EXTENSION_NAME);
            _settings.fillRectangleNV = true;
        }
        else
        {
            if (!deviceInfo.fillRectangleNV && deviceSettings.fillRectangleNV)
                throw std::runtime_error("DeviceCoreSimplifierInternal::CreateDevice Error: Program tried to create logical device with Nvidia's fill rectangle extension enabled on an uncompatible physical device!");

            _settings.fillRectangleNV = false;
        }

        if (deviceInfo.swapchainExtension && deviceSettings.swapchainExtension)
        {
            _requestedExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            _settings.swapchainExtension = true;
        }
        else
        {
            if (!deviceInfo.swapchainExtension && deviceSettings.swapchainExtension)
                throw std::runtime_error("DeviceCoreSimplifierInternal::CreateDevice Error: Program tried to create logical device with swapchain extension enabled on an uncompatible physical device!");

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
    }

    DeviceCoreSimplifierInternal::~DeviceCoreSimplifierInternal()
    {
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

    SimplifiedDeviceInfo DeviceCoreSimplifierInternal::GetDeviceInfo() const
    {
        return _info;
    }

    uint32_t DeviceCoreSimplifierInternal::GetBestQueueForTheType(QueueFamilyType type) const
    {
        std::optional<uint32_t> ret;

        auto& families = _info.queueFamilies;

        switch (type)
        {
        case VulkanSimplified::QueueFamilyType::TRANSFER:
            if (families.transferFamily.has_value())
                ret = families.transferFamily;
            else
            {
                if (families.computeFamily.has_value())
                    ret = families.computeFamily;
                else
                    ret = families.graphicsFamily;
            }
            break;
        case VulkanSimplified::QueueFamilyType::COMPUTE:
            if (families.computeFamily.has_value())
                ret = families.computeFamily;
            else
                ret = families.graphicsFamily;
            break;
        case VulkanSimplified::QueueFamilyType::GRAPHICS:
            ret = families.graphicsFamily;
            break;
        default:
            throw std::runtime_error("DeviceCoreSimplifierInternal::GetBestQueueForTheType Error: Program was given an erroneous value of queue family type!");
        }

        if (!ret.has_value())
            throw std::runtime_error("DeviceCoreSimplifierInternal::GetBestQueueForTheType Error: Program can't find any queue of any compatible family!");

        return ret.value();
    }

    VkQueue DeviceCoreSimplifierInternal::GetQueue(QueueFamilyType queueType) const
    {
        VkQueue ret = VK_NULL_HANDLE;

        switch (queueType)
        {
        case VulkanSimplified::QueueFamilyType::TRANSFER:
            ret = _transferQueue;
            break;
        case VulkanSimplified::QueueFamilyType::COMPUTE:
            ret = _computeQueue;
            break;
        case VulkanSimplified::QueueFamilyType::GRAPHICS:
            ret = _graphicQueue;
            break;
        default:
            throw std::runtime_error("DeviceCoreSimplifierInternal::GetQueue Error: Program was given an erroneous queue type!");
        }

        return ret;
    }

    void DeviceCoreSimplifierInternal::WaitForIdleness()
    {
        vkDeviceWaitIdle(_device);
    }

}