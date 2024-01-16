#pragma once

namespace VulkanSimplified
{
    class SurfaceSimplifier
    {
        VkSurfaceKHR _surface;

    public:
        SurfaceSimplifier(SDL_Window* window, const VkInstance instance);
        ~SurfaceSimplifier();

        VkSurfaceKHR GetSurface() const;

        void PreDestructionCall(const VkInstance instance);
    };
}
