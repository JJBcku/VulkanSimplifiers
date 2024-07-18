module MainSettings;

MainSettings::MainSettings()
{
	_quit = false;
	for (size_t i = 0; i < sizeof(_padding); i++)
		_padding[i] = 0;
}

MainSettings::~MainSettings()
{
}

bool MainSettings::GetQuit() const
{
	return _quit;
}

bool MainSettings::QuitEventCallback(const SDLModuleQuitEvent&, void* instance)
{
	if (instance != nullptr)
	{
		MainSettings* pointer = static_cast<MainSettings*>(instance);
		pointer->SetQuit();
		return false;
	}

	return true;
}

void MainSettings::SetQuit()
{
	std::lock_guard<std::mutex> guard(lock);
	_quit = true;
}