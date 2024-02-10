#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	struct ShaderContainer
	{
		VkShaderModule _module;
		VkDevice _device;
		void* _ppadding;
		uint64_t _codeSize;

		ShaderContainer();
		~ShaderContainer();

		ShaderContainer(const ShaderContainer&) noexcept = delete;
		ShaderContainer(ShaderContainer&& other) noexcept;

		ShaderContainer& operator=(const ShaderContainer&) noexcept = delete;
		ShaderContainer& operator=(ShaderContainer&& other) noexcept;

		VkShaderModule GetShaderModule() const;
	};

	class ShaderModulesSimplifierInternal
	{
		VkDevice _device;
		void* _ppadding;

		ListTemplate<ShaderContainer> _shaderModules;

	public:
		ShaderModulesSimplifierInternal(VkDevice device, size_t reserve = 0);
		~ShaderModulesSimplifierInternal();

		ShaderModulesSimplifierInternal(const ShaderModulesSimplifierInternal&) noexcept = delete;
		ShaderModulesSimplifierInternal(ShaderModulesSimplifierInternal&&) noexcept = default;

		ShaderModulesSimplifierInternal& operator=(const ShaderModulesSimplifierInternal&) noexcept = delete;
		ShaderModulesSimplifierInternal& operator=(ShaderModulesSimplifierInternal&&) noexcept = default;

		ListObjectID<ShaderContainer> CreateShaderModule(const std::vector<unsigned char>& shaderCode);

		VkShaderModule GetShaderModule(ListObjectID<ShaderContainer> shaderModuleID) const;
	};
}
