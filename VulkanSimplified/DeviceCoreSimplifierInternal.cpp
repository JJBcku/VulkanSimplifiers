#include "pch.h"
#include "DeviceCoreSimplifierInternal.h"

#include "Include/BasicsSimplifierSharedStructs.h"
#include "Include/DeviceSimplifierSharedStructs.h"

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

    DeviceCoreSimplifierInternal::DeviceCoreSimplifierInternal(VkPhysicalDevice device, SimplifiedDeviceInfo deviceInfo, DeviceSettings deviceSettings)
    {
        _device = VK_NULL_HANDLE;
        _info = deviceInfo;
        _settings = deviceSettings;

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

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queues.size());
        if (!queues.empty())
            createInfo.pQueueCreateInfos = queues.data();

        createInfo.enabledExtensionCount = static_cast<uint32_t>(_requestedExtensions.size());
        if (!_requestedExtensions.empty())
            createInfo.ppEnabledExtensionNames = _requestedExtensions.data();

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

    DeviceCoreSimplifierInternal::~DeviceCoreSimplifierInternal()
    {
        if (_device != VK_NULL_HANDLE)
        {
            vkDestroyDevice(_device, nullptr);
        }
    }
}