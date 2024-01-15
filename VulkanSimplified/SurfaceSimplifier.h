#pragma once

namespace VulkanSimplified
{
    class SurfaceSimplifier
    {
        VkSurfaceKHR _surface;

    public:
        SurfaceSimplifier(SDL_Window* window, const VkInstance instance);
        ~SurfaceSimplifier();

        void PreDestructionCall(const VkInstance instance);
    };
}
