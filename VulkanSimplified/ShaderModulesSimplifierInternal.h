#pragma once

#include "Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	struct ShaderContainer
	{
		VkShaderModule _module;
		VkDevice _device;
		uint64_t _codeSize;

		ShaderContainer();
		~ShaderContainer();

		ShaderContainer(const ShaderContainer&) noexcept = delete;
		ShaderContainer(ShaderContainer&& other) noexcept;

		ShaderContainer& operator=(const ShaderContainer&) noexcept = delete;
		ShaderContainer& operator=(ShaderContainer&& other) noexcept;
	};

	class ShaderModulesSimplifierInternal
	{
		const VkDevice _device;

		ListTemplate<ShaderContainer> _shaderModules;

	public:
		ShaderModulesSimplifierInternal(VkDevice device, size_t reserve = 0);
		~ShaderModulesSimplifierInternal();

		ShaderModulesSimplifierInternal(const ShaderModulesSimplifierInternal&) noexcept = delete;
		ShaderModulesSimplifierInternal(ShaderModulesSimplifierInternal&&) noexcept = delete;

		ShaderModulesSimplifierInternal& operator=(const ShaderModulesSimplifierInternal&) noexcept = delete;
		ShaderModulesSimplifierInternal& operator=(ShaderModulesSimplifierInternal&&) noexcept = delete;

		ListObjectID<ShaderContainer> CreateShaderModule(const std::vector<unsigned char>& shaderCode);
	};
}
