#pragma once

namespace VulkanSimplified
{
    class SurfaceSimplifierInternal
    {
        VkSurfaceKHR _surface;

    public:
        SurfaceSimplifierInternal(SDL_Window* window, const VkInstance instance);
        ~SurfaceSimplifierInternal();

        VkSurfaceKHR GetSurface() const;

        void PreDestructionCall(const VkInstance instance);
    };
}
