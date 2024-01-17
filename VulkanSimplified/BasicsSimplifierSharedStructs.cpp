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
        discreteGPU = false;

        padding[0] = 0;
        padding[1] = 0;

        deviceApiVersion = 0;
        upadding = 0;
    }

}