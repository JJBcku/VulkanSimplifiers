#include "stdafx.h"

#include <BasicsSimplifier.h>

int main()
{
    using VulkanSimplified::WindowCreationData;
    using VulkanSimplified::BasicsSimplifier;

    std::cout << "Vulkan Simplified testing started!\n";

    WindowCreationData windowSettings{};

    windowSettings.windowTitle = "Vulkan Simplified Test Window";
    windowSettings.windowHeight = 600;
    windowSettings.windowWidth = 800;
    windowSettings.properties = VulkanSimplified::WindowProperties::NONE;

    std::unique_ptr<BasicsSimplifier> main = std::make_unique<BasicsSimplifier>(windowSettings);

    main.reset();

    std::cout << "Vulkan Simplified testing successful!\n";

    return 0;
}
