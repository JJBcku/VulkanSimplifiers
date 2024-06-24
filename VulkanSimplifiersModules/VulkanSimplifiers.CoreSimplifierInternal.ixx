export module VulkanSimplifiers.CoreSimplifierInternal;

namespace VulkanSimplifiers
{
	export class CoreSimplifierInternal
	{
	public:
		explicit CoreSimplifierInternal(size_t reserve);
		~CoreSimplifierInternal();
	private:
		size_t stump;
	};
}