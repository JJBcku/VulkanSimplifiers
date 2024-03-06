#pragma once

namespace VulkanSimplified
{
	class ShaderModulesSimplifierInternal;

	struct ShaderContainer;

	template<class T>
	class ListObjectID;

	class ShaderModulesSimplifier
	{
		ShaderModulesSimplifierInternal& _internal;

	public:
		ShaderModulesSimplifier(ShaderModulesSimplifierInternal& reference);
		~ShaderModulesSimplifier();

		ShaderModulesSimplifier(const ShaderModulesSimplifier&) noexcept = delete;
		ShaderModulesSimplifier(ShaderModulesSimplifier&&) noexcept = delete;

		ShaderModulesSimplifier& operator=(const ShaderModulesSimplifier&) noexcept = delete;
		ShaderModulesSimplifier& operator=(ShaderModulesSimplifier&&) noexcept = delete;

		ListObjectID<ShaderContainer> CreateShaderModule(const std::vector<unsigned char>& shaderCode);
	};
}


