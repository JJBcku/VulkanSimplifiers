#pragma once

namespace VulkanSimplified
{
    class WindowSimplifierInternal;
    class VulkanCoreSimplifierInternal;

    class SurfaceSimplifierInternal
    {
        VkSurfaceKHR _surface;

        const WindowSimplifierInternal& _windowSimplifier;
        const VulkanCoreSimplifierInternal& _coreSimplifier;

        void DestroySurface();

    public:
        SurfaceSimplifierInternal(const WindowSimplifierInternal& windowSimplifier, const VulkanCoreSimplifierInternal& coreSimplifier);
        ~SurfaceSimplifierInternal() noexcept;

        SurfaceSimplifierInternal& operator=(const SurfaceSimplifierInternal&) noexcept = delete;

        VkSurfaceKHR GetSurface() const;
    };
}
