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

    MemoryHeapSizes::MemoryHeapSizes()
    {
        externalUncachedDeviceAccessibleMemorySize = 0;
        externalCachedCoherentDeviceAccessibleMemorySize = 0;
        externalCachedIncoherentDeviceAccessibleMemorySize = 0;
        localMemorySize = 0;
        sharedUncachedMemorySize = 0;
        sharedCachedCoherentMemorySize = 0;
        sharedCachedIncoherentMemorySize = 0;
    }

}