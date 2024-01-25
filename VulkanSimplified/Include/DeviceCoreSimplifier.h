#pragma once

namespace VulkanSimplified
{
	class DeviceCoreSimplifierInternal;
	class ShaderModulesSimplifier;

	class DeviceCoreSimplifier
	{
		DeviceCoreSimplifierInternal& _internal;

	public:
		DeviceCoreSimplifier(DeviceCoreSimplifierInternal& reference);
		~DeviceCoreSimplifier();

		DeviceCoreSimplifier(const DeviceCoreSimplifier&) noexcept = delete;

		DeviceCoreSimplifier& operator=(const DeviceCoreSimplifier&) noexcept = delete;

		ShaderModulesSimplifier GetShaderModulesSimplifier();
	};
}


