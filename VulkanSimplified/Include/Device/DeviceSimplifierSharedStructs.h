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
		std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> _commandBuffers;
		std::vector<ListObjectID<AutoCleanupSemaphore>> _signalSemaphores;
	};

	class AutoCleanupSharedUncachedDeviceMemory;
	class AutoCleanupSharedCachedCoherentDeviceMemory;
	class AutoCleanupSharedCachedIncoherentDeviceMemory;

	union SharedDeviceMemoryID
	{
		MemoryPropertiesIDType type = MemoryPropertiesIDType::NONE;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupSharedUncachedDeviceMemory> ID;
		} _unchachedID;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory> ID;
		} _cachedCoherentID;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory> ID;
		} _cachedIncoherentID;
	};

	class AutoCleanupAccesibleUncachedHostMemory;
	class AutoCleanupAccesibleCachedCoherentHostMemory;
	class AutoCleanupAccesibleCachedIncoherentHostMemory;

	union AccessibleHostMemoryID
	{
		MemoryPropertiesIDType type = MemoryPropertiesIDType::NONE;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupAccesibleUncachedHostMemory> ID;
		} _unchachedID;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory> ID;
		} _cachedCoherentID;
		struct
		{
			MemoryPropertiesIDType type;
			ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory> ID;
		} _cachedIncoherentID;
	};

	class AutoCleanupExclusiveDeviceMemory;

	union MemoryID
	{
		MemoryType memoryType;
		struct
		{
			MemoryType memoryType;
			SharedDeviceMemoryID ID;
		} _sharedID;
		struct
		{
			MemoryType memoryType;
			AccessibleHostMemoryID ID;
		} _hostID;
		struct
		{
			MemoryType memoryType;
			ListObjectID<AutoCleanupExclusiveDeviceMemory> ID;
		} _exclusiveID;

		MemoryID()
		{
			memset(&memoryType, 0, sizeof(memoryType));
		}

		MemoryID(SharedDeviceMemoryID sharedID)
		{
			_sharedID.memoryType = MemoryType::SHARED;
			_sharedID.ID = sharedID;
		}

		MemoryID(AccessibleHostMemoryID hostID)
		{
			_hostID.memoryType = MemoryType::HOST;
			_hostID.ID = hostID;
		}

		MemoryID(ListObjectID<AutoCleanupExclusiveDeviceMemory> exclusiveID)
		{
			_exclusiveID.memoryType = MemoryType::EXCLUSIVE;
			_exclusiveID.ID = exclusiveID;
		}
	};

	struct BufferCopyOrder
	{
		uint64_t sourceOffset = 0;
		uint64_t destinationOffset = 0;
		uint64_t dataSize = 0;
	};

	class AutoCleanupDescriptorPool;

	struct CommonDescriptorSetWriteOrder
	{
		ListObjectID<AutoCleanupDescriptorPool> poolID;
		uint32_t binding = std::numeric_limits<uint32_t>::max();
		uint32_t firstArrayElement = std::numeric_limits<uint32_t>::max();
	};

	class UniformBufferDescriptorSet;
	class AutoCleanupDescriptorSetsBuffer;

	struct DescriptorSetBufferWriteOrder
	{
		std::optional<ListObjectID<AutoCleanupDescriptorSetsBuffer>> objectID;
		uint64_t offset = std::numeric_limits<uint64_t>::max();
		std::optional<uint64_t> range = 0;
	};

	class UniformBufferDescriptorSet;

	struct DescriptorSetUniformBufferWriteOrder : public CommonDescriptorSetWriteOrder
	{
		ListObjectID<UniformBufferDescriptorSet> descriptorID;
		std::vector<DescriptorSetBufferWriteOrder> writeOrdersBufferData;
		char padding[16 - (sizeof(writeOrdersBufferData) % 16)];
	};

	struct DescriptorSetUniformBufferCopyObjectInfo
	{
		ListObjectID<AutoCleanupDescriptorPool> poolID;
		ListObjectID<UniformBufferDescriptorSet> descriptorID;
		uint32_t binding = 0;
		uint32_t firstArrayElement = 0;
	};

	struct DescriptorSetUniformBufferCopyOrder
	{
		DescriptorSetUniformBufferCopyObjectInfo srcBuffer;
		DescriptorSetUniformBufferCopyObjectInfo dstBuffer;
		uint32_t amountOfArrayElementsToCopy = 0;
		uint32_t padding = 0;
	};

	struct UniformBufferDescriptorSetID
	{
		ListObjectID<AutoCleanupDescriptorPool> poolID;
		ListObjectID<UniformBufferDescriptorSet> descriptorID;
	};
}