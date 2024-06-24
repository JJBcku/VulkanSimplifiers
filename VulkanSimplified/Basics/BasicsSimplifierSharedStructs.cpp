#include "../Other/pch.h"
#include "../Include/Basics/BasicsSimplifierSharedStructs.h"

namespace VulkanSimplified
{

    AvailableColorsList::AvailableColorsList()
    {
        NormalColor = false;
        HDRColor = false;
        OneAndHalfColor = false;
        DoubleColor = false;
    }

    AvailableCompressedTexturesList::AvailableCompressedTexturesList()
    {
        bc = false;
        etc2ANDeac = false;
        astc_LDR = false;
        astc_HDR = false;
    }

    SimplifiedDeviceInfo::SimplifiedDeviceInfo() : renderingColorList()
    {
        unrestrictedDepth = false;
        fillRectangleNV = false;
        swapchainExtension = false;
        discreteGPU = false;

        mailboxPresentMode = false;
        fifoPresentMode = false;

        memset(padding, 0, sizeof(padding));

        deviceApiVersion = 0;
        //upadding = 0;

        minSwapchainImages = 0;
        maxSwapchainImages = 0;
    }

    QueueFamilies::QueueFamilies()
    {
    }

    MemoryHeapSizes::MemoryHeapSizes() : externalMemory(), sharedMemory()
    {
        localMemorySize = 0;
    }

    ExternalMemoryHeapSizes::ExternalMemoryHeapSizes()
    {
        uncached = 0;
        cachedCoherent = 0;
        cachedIncoherent = 0;
    }

    SharedMemoryHeapSizes::SharedMemoryHeapSizes()
    {
        uncached = 0;
        cachedCoherent = 0;
        cachedIncoherent = 0;
    }

}