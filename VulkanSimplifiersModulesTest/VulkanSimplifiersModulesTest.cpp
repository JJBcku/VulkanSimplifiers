import VulkanSimplifiers.Core.Simplifier;
import ListTemplates.IDObject;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Simplifier;
import std;

int main()
{
    CoreSimplifier core(0x10, 0x10);

    WindowCreationData window;

    window.windowTitle = "Module Test Window";
    window.windowWidth = 800;
    window.windowHeight = 600;

    auto windowId = core.CreateWindow(window, 0);

    auto windowSimplifier = core.GetWindowSimplifier(windowId);
}
