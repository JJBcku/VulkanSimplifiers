#include "pch.h"
#include "ShaderModulesSimplifierInternal.h"

namespace VulkanSimplified
{

	ShaderModulesSimplifierInternal::ShaderModulesSimplifierInternal(VkDevice device, size_t reserve) : _device(device), _shaderModules(reserve)
	{
	}

	ShaderModulesSimplifierInternal::~ShaderModulesSimplifierInternal()
	{
		_shaderModules.Reset();
	}

	ListObjectID<ShaderContainer> ShaderModulesSimplifierInternal::CreateShaderModule(const std::vector<unsigned char>& shaderCode)
	{
		if ((shaderCode.size() & 3) != 0)
			throw std::runtime_error("ShaderModulesSimplifier::CreateShaderModule Error: Program tried to create shader module from code whoose size is not a muliple of 4!");

		ShaderContainer add;

		add._codeSize = shaderCode.size();
		add._device = _device;

		if (add._codeSize > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("ShaderModulesSimplifier::CreateShaderModule Error: Program tried to create shader module with too big size for vulkan too handle!");
		
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;;
		createInfo.codeSize = static_cast<uint32_t>(add._codeSize);
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

		if (vkCreateShaderModule(_device, &createInfo, nullptr, &add._module) != VK_SUCCESS)
			throw std::runtime_error("ShaderModulesSimplifier::CreateShaderModule Error: Program failed to create a shader module!");

		return _shaderModules.AddObject(std::move(add));
	}

	ShaderContainer::ShaderContainer()
	{
		_module = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
		_codeSize = 0;
	}

	ShaderContainer::~ShaderContainer()
	{
		if (_module != VK_NULL_HANDLE)
		{
			vkDestroyShaderModule(_device, _module, nullptr);
		}
	}

	ShaderContainer::ShaderContainer(ShaderContainer&& other) noexcept
	{
		_device = other._device;
		other._device = VK_NULL_HANDLE;

		_codeSize = other._codeSize;
		other._codeSize = 0;

		_module = other._module;
		other._module = VK_NULL_HANDLE;
	}

	ShaderContainer& ShaderContainer::operator=(ShaderContainer&& other) noexcept
	{
		_device = other._device;
		other._device = VK_NULL_HANDLE;

		_codeSize = other._codeSize;
		other._codeSize = 0;

		_module = other._module;
		other._module = VK_NULL_HANDLE;

		return *this;
	}

}
