export module VulkanSimplifiers.CoreSimplifier;

import VulkanSimplifiers.CoreSimplifierInternal;
import std;

namespace VulkanSimplifiers
{
	export class CoreSimplifier
	{
	public:
		explicit CoreSimplifier(size_t reserve);
		~CoreSimplifier();
	private:
		CoreSimplifierInternal _internal;
	};
}