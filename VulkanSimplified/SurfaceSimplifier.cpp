#include "pch.h"
#include "SurfaceSimplifier.h"

namespace VulkanSimplified
{

    SurfaceSimplifier::SurfaceSimplifier(SDL_Window* window, const VkInstance instance)
    {
        if (window == nullptr)
            throw std::runtime_error("Error: Program tried to create a surface for non-existent window!");

        _surface = VK_NULL_HANDLE;

        if (SDL_Vulkan_CreateSurface(window, instance, &_surface) != SDL_TRUE)
            throw std::runtime_error("Error: Program failed to create a window's surface!");
    }

    SurfaceSimplifier::~SurfaceSimplifier()
    {
    }

    VkSurfaceKHR SurfaceSimplifier::GetSurface() const
    {
        return _surface;
    }

    void SurfaceSimplifier::PreDestructionCall(const VkInstance instance)
    {
        if (_surface != VK_NULL_HANDLE)
            vkDestroySurfaceKHR(instance, _surface, nullptr);

        _surface = VK_NULL_HANDLE;
    }

}
