export module VulkanSimplifiers.Window;

import VulkanSimplifiers.Window.Internal;

export class WindowSimplifier
{
public:
	WindowSimplifier(WindowInternal& ref);
	~WindowSimplifier();

	WindowSimplifier& operator=(WindowSimplifier&) const = delete;

	bool GetQuit() const;
	bool GetPaused() const;
	bool GetResized();

private:
	WindowInternal& _internal;
};