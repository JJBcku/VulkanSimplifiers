import VulkanSimplifiers.Core.Simplifier;
import VulkanSimplifiers.EventHandler.Simplifier;
import ListTemplates.IDObject;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Simplifier;
import std;

import MainSettings;

int main()
{
    MainSettings settings;

    CoreSimplifier core(0x10, 0x10, 0x10);

    auto eventHandler = core.GetEventHandler();
    eventHandler.RegisterQuitEventCallback(settings.QuitEventCallback, &settings, 0x10);

    WindowCreationData window;

    window.windowTitle = "Module Test Window";
    window.windowWidth = 800;
    window.windowHeight = 600;

    auto windowId = core.CreateWindow(window, 0);

    auto windowSimplifier = core.GetWindowSimplifier(windowId);

    while (!settings.GetQuit())
    {
        eventHandler.HandleEvents();
        std::this_thread::sleep_for(std::chrono::duration<double, std::nano>(100));
    }
}
