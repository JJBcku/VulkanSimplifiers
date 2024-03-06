#pragma once

#include "DeviceSimplifierSharedEnums.h"
#include "../SharedData/SharedDataSimplifierEnums.h"
#include "../Common/ListObjectID.h"

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

	class AutoCleanupFence;
	class AutoCleanupSemaphore;
	class DeviceCommandRecorderInternal;

	struct QueueSubmitObject
	{
		std::vector<std::pair<PipelineStage, ListObjectID<AutoCleanupSemaphore>>> _waitSemaphores;
		std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> _commandBuffer;
		std::vector<ListObjectID<AutoCleanupSemaphore>> _signalSemaphores;
	};

	class AutoCleanupSharedUncachedDeviceMemory;
	class AutoCleanupSharedCachedCoherentDeviceMemory;
	class AutoCleanupSharedCachedIncoherentDeviceMemory;

	union SharedDeviceMemoryID
	{
		MemoryPropertiesIDType _type = MemoryPropertiesIDType::NONE;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupSharedUncachedDeviceMemory> _ID;
		} _unchachedID;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> _ID;
		} _cachedCoherentID;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> _ID;
		} _cachedIncoherentID;
	};

	class AutoCleanupAccesibleUncachedExternalMemory;
	class AutoCleanupAccesibleCachedCoherentExternalMemory;
	class AutoCleanupAccesibleCachedIncoherentExternalMemory;

	union ExternalAccessibleMemoryID
	{
		MemoryPropertiesIDType _type = MemoryPropertiesIDType::NONE;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupAccesibleUncachedExternalMemory> _ID;
		} _unchachedID;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupAccesibleCachedCoherentExternalMemory> _ID;
		} _cachedCoherentID;
		struct
		{
			MemoryPropertiesIDType _type;
			ListObjectID<AutoCleanupAccesibleCachedIncoherentExternalMemory> _ID;
		} _cachedIncoherentID;
	};
}