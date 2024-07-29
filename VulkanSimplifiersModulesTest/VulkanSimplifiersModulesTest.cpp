import VulkanSimplifiers.Main;
import VulkanSimplifiers.Main.Data;
import VulkanSimplifiers.EventHandling;
import ListTemplates.IDObject;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window;
import VulkanSimplifiers.WindowList;
import VulkanSimplifiers.InstanceList;
import std;

import MainSettings;

int main()
{
    MainSettings settings;

    MainSimplifierInitData initData;

    initData.appVersion.patch = 1;
    initData.appTitle = "Vulkan Simplifier test app";

    MainSimplifier core(initData);

    auto eventHandler = core.GetEventHandler();
    eventHandler.RegisterQuitEventCallback(settings.QuitEventCallback, &settings, 0x10);

    WindowCreationData window;

    window.windowTitle = "Module Test Window";
    window.windowWidth = 800;
    window.windowHeight = 600;

    auto windowList = core.GetWindowListSimplifier();

    auto windowId = windowList.CreateWindow(window);

    auto windowSimplifier = windowList.GetWindowSimplifier(windowId);

    auto instanceList = core.GetInstanceListSimplifier();

    while (!settings.GetQuit())
    {
        eventHandler.HandleEvents();
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
    }
}
