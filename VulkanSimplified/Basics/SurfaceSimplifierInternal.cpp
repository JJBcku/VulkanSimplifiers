#include "../Other/pch.h"
#include "SurfaceSimplifierInternal.h"

#include "WindowSimplifierInternal.h"
#include "VulkanCoreSimplifierInternal.h"

namespace VulkanSimplified
{

    SurfaceSimplifierInternal::SurfaceSimplifierInternal(const WindowSimplifierInternal& windowSimplifier, const VulkanCoreSimplifierInternal& coreSimplifier) : _windowSimplifier(windowSimplifier), _coreSimplifier(coreSimplifier)
    {
        auto window = windowSimplifier.GetWindow();
        assert(window != nullptr);

        _surface = VK_NULL_HANDLE;
        
        assert(coreSimplifier.GetInstance() != VK_NULL_HANDLE);

        if (SDL_Vulkan_CreateSurface(window, coreSimplifier.GetInstance(), &_surface) != SDL_TRUE)
            throw std::runtime_error("Error: Program failed to create a window's surface!");
    }

    SurfaceSimplifierInternal::~SurfaceSimplifierInternal() noexcept
    {
        DestroySurface();
    }

    VkSurfaceKHR SurfaceSimplifierInternal::GetSurface() const
    {
        return _surface;
    }

    void SurfaceSimplifierInternal::DestroySurface()
    {
        if (_surface != VK_NULL_HANDLE)
        {
            auto instance = _coreSimplifier.GetInstance();
            assert(instance != VK_NULL_HANDLE);

            vkDestroySurfaceKHR(instance, _surface, nullptr);
            _surface = VK_NULL_HANDLE;
        }
    }

}
