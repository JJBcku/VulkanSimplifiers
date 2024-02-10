#pragma once

#include "DeviceSimplifierSharedEnums.h"
#include "VulkanSimplifierListTemplate.h"

struct VkDescriptorSetLayoutBinding;
struct VkPipelineInputAssemblyStateCreateInfo;
struct VkPipelineRasterizationStateCreateInfo;
struct VkPipelineMultisampleStateCreateInfo;
struct VkPipelineDepthStencilStateCreateInfo;

namespace VulkanSimplified
{
	struct DeviceSettings
	{
		bool unrestrictedDepth;
		bool fillRectangleNV;
		bool swapchainExtension;
		char padding[5];

		DeviceSettings();
	};

	struct SwapchainSettings
	{
		SwapchainFormatType format;
		SwapchainPresentMode presentMode;
		SwapchainImageAmount imageAmount;
	};

	struct ShaderContainer;
	struct ShaderStageCreationData;
	struct VertexInputList;
	struct PipelineViewportsStateList;
	struct ColorBlendSettings;

	class AutoCleanupPipelineLayout;
	class AutoCleanupRenderPass;
	class AutoCleanupGraphicsPipeline;

	union BaseGraphicPipelineID
	{
		BasePipelineIDType _idType;
		struct OutsideID {
			BasePipelineIDType _outsideIDType = VulkanSimplified::BasePipelineIDType::NONE;
			ListObjectID<AutoCleanupGraphicsPipeline> _basePipelineOutsideID = ListObjectID<AutoCleanupGraphicsPipeline>();
		} _outsideID;
		struct InsideID {
			BasePipelineIDType _currentListIDType;
			size_t _basePipelineCurrentListID, padding;
		} _insideID;

		BaseGraphicPipelineID() : _outsideID() { };
	};

	struct GraphicsPipelineCreateInfoList
	{
		std::vector<std::pair<ListObjectID<ShaderContainer>, ListObjectID<ShaderStageCreationData>>> _shaderStagesDataList;
		char cpadding[16 - (sizeof(_shaderStagesDataList) % 8)];
		ListObjectID<VertexInputList> _vertexInput;
		ListObjectID<VkPipelineInputAssemblyStateCreateInfo> _inputAssembly;
		ListObjectID<PipelineViewportsStateList> _viewportState;
		ListObjectID<VkPipelineRasterizationStateCreateInfo> _rasterizationState;
		ListObjectID<VkPipelineMultisampleStateCreateInfo> _multisamplingState;
		std::optional<ListObjectID<VkPipelineDepthStencilStateCreateInfo>> _depthStencilState;
		ListObjectID<ColorBlendSettings> _colorBlendState;
		ListObjectID<AutoCleanupPipelineLayout> _pipelineLayout;
		ListObjectID<AutoCleanupRenderPass> _renderPass;
		uint32_t _subpass, _upadding;
		BaseGraphicPipelineID _basePipelineID;

		bool _allowDerivatives;
		char ccpadding[7];
	};
}