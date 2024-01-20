#include "pch.h"
#include "Include/BasicsSimplifierSharedStructs.h"

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
        discreteGPU = false;

        padding = 0;

        deviceApiVersion = 0;
        upadding = 0;

        nonLocalMemorySize = 0;
        localMemorySize = 0;
        sharedMemorySize = 0;
    }

    QueueFamilies::QueueFamilies()
    {
    }

}