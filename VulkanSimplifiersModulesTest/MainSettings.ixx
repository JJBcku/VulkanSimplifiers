export module MainSettings;

import VulkanSimplifiers.EventHandler.SDLModule.QuitEvent;

import std;

export class MainSettings
{
public:
	MainSettings();
	~MainSettings();

	MainSettings(const MainSettings&) noexcept = delete;

	MainSettings& operator=(const MainSettings&) noexcept = delete;

	bool GetQuit() const;

	static bool QuitEventCallback(const SDLModuleQuitEvent&, void* instance);

private:
	std::mutex lock;
	bool _quit;
	char _padding[7];

	void SetQuit();
};