#include "pch.h"
#include "SurfaceSimplifierInternal.h"

namespace VulkanSimplified
{

    SurfaceSimplifierInternal::SurfaceSimplifierInternal(SDL_Window* window, const VkInstance instance)
    {
        if (window == nullptr)
            throw std::runtime_error("Error: Program tried to create a surface for non-existent window!");

        _surface = VK_NULL_HANDLE;

        if (SDL_Vulkan_CreateSurface(window, instance, &_surface) != SDL_TRUE)
            throw std::runtime_error("Error: Program failed to create a window's surface!");
    }

    SurfaceSimplifierInternal::~SurfaceSimplifierInternal()
    {
    }

    VkSurfaceKHR SurfaceSimplifierInternal::GetSurface() const
    {
        return _surface;
    }

    void SurfaceSimplifierInternal::PreDestructionCall(const VkInstance instance)
    {
        if (_surface != VK_NULL_HANDLE)
            vkDestroySurfaceKHR(instance, _surface, nullptr);

        _surface = VK_NULL_HANDLE;
    }

}
