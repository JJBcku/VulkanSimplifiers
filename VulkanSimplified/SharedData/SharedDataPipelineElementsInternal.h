#pragma once

#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Include/SharedData/SharedDataSimplifierEnums.h"

bool operator==(const VkVertexInputBindingDescription& first, const VkVertexInputBindingDescription& second);
bool operator==(const VkVertexInputAttributeDescription& first, const VkVertexInputAttributeDescription& second);

bool operator==(const VkPipelineInputAssemblyStateCreateInfo& first, const VkPipelineInputAssemblyStateCreateInfo& second);
bool operator==(const VkPipelineRasterizationStateCreateInfo& first, const VkPipelineRasterizationStateCreateInfo& second);
bool operator==(const VkPipelineMultisampleStateCreateInfo& first, const VkPipelineMultisampleStateCreateInfo& second);
bool operator==(const VkPipelineDepthStencilStateCreateInfo& first, const VkPipelineDepthStencilStateCreateInfo& second);
bool operator==(const VkPipelineColorBlendAttachmentState& first, const VkPipelineColorBlendAttachmentState& second);

bool operator==(const VkViewport& first, const VkViewport& second);
bool operator==(const VkOffset2D& first, const VkOffset2D& second);
bool operator==(const VkExtent2D& first, const VkExtent2D& second);
bool operator==(const VkRect2D& first, const VkRect2D& second);
bool operator==(const VkClearValue& first, const VkClearValue& second);
bool operator==(const VkClearColorValue& first, const VkClearColorValue& second);
bool operator==(const VkClearDepthStencilValue& first, const VkClearDepthStencilValue& second);

namespace VulkanSimplified
{
	struct VertexInputList
	{
		std::vector<ListObjectID<VkVertexInputBindingDescription>> _bindings;
		std::vector<ListObjectID<VkVertexInputAttributeDescription>> _attributes;

		bool operator==(const VertexInputList& other) const noexcept;
	};

	struct ShaderContainer;

	struct ShaderStageCreationData
	{
		ShaderStageType _stage;
		const char* _name;
		void* _ppadding;

	public:
		ShaderStageCreationData(ShaderStageType stage, const char* name);

		bool operator==(const ShaderStageCreationData& other) const noexcept;
	};

	struct PipelineViewportsStateList
	{
		std::vector<std::pair<ListObjectID<VkViewport>, ListObjectID<VkRect2D>>> _viewportScissorPairs;

		bool operator==(const PipelineViewportsStateList& other) const noexcept;
	};

	struct ColorBlendSettings
	{
		std::vector<ListObjectID<VkPipelineColorBlendAttachmentState>> _attachments;
		float _blendConstantR;
		float _blendConstantG;
		float _blendConstantB;
		float _blendConstantA;

		bool operator==(const ColorBlendSettings&) const noexcept;
	};

	class SharedDataPipelineElementsInternal
	{
		ListTemplate<ShaderStageCreationData> _shaderPipelineData;

		ListTemplate<VkVertexInputBindingDescription> _vertexInputBindingDescriptions;
		ListTemplate<VkVertexInputAttributeDescription> _vertexInputAttributeDescriptions;

		ListTemplate<VertexInputList> _vertexInputListDescriptions;

		ListTemplate<VkPipelineInputAssemblyStateCreateInfo> _pipelineInputAssembly;
		ListTemplate<VkPipelineRasterizationStateCreateInfo> _pipelineRasterizationStates;
		ListTemplate<VkPipelineMultisampleStateCreateInfo> _pipelineMultiSampleStates;
		ListTemplate<VkPipelineDepthStencilStateCreateInfo> _pipelineDepthStencilStates;
		ListTemplate<VkPipelineColorBlendAttachmentState> _pipelineBlendAttachmentStates;
		ListTemplate<ColorBlendSettings> _pipelineColorBlendStates;

		ListTemplate<VkViewport> _pipelineViewports;
		ListTemplate<VkRect2D> _pipelineScissors;
		ListTemplate<PipelineViewportsStateList> _pipelineViewportStates;

		ListTemplate<VkClearValue> _clearValues;

		ListObjectID<VkClearValue> AddClearValue(VkClearValue value);

	public:
		SharedDataPipelineElementsInternal(size_t reserve);
		~SharedDataPipelineElementsInternal();

		SharedDataPipelineElementsInternal(const SharedDataPipelineElementsInternal&) noexcept = delete;

		SharedDataPipelineElementsInternal& operator=(const SharedDataPipelineElementsInternal&) noexcept = delete;

		ListObjectID<ShaderStageCreationData> AddShaderPipelineData(ShaderStageType stage, const char* mainFunctionName);

		ListObjectID<VkVertexInputBindingDescription> AddBindingDescription(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes, bool useInstanceIndex);
		ListObjectID<VkVertexInputAttributeDescription> AddAttributeDescription(uint32_t location, uint32_t binding, VertexAttributeFormats format, uint32_t offset);
		std::vector<ListObjectID<VkVertexInputAttributeDescription>> AddAttributeDescriptions(uint32_t binding, const std::vector<VertexAttributeFormats>& attributes);

		ListObjectID<VertexInputList> AddVertexInputList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& bindings, const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& attributes);

		ListObjectID<VkPipelineInputAssemblyStateCreateInfo> AddPipelineInputAssembly(TopologySetting topology);
		ListObjectID<VkPipelineRasterizationStateCreateInfo> AddPipelineRasterizationState(PipelinePolygonMode polygonMode, PipelineCullMode cullMode, bool clockwiseFront);
		ListObjectID<VkPipelineMultisampleStateCreateInfo> AddPipelineMultisampleState(PipelineMultisampleCount multisampling, bool sampleShading, float minSampleShading);
		ListObjectID<VkPipelineDepthStencilStateCreateInfo> AddPipelineDepthState(bool depthTest, bool depthWrite, PipelineDepthCompare compare);
		ListObjectID<VkPipelineColorBlendAttachmentState> AddPipelineColorBlendAttachment(PipelineBlendSettings settings);
		ListObjectID<ColorBlendSettings> AddPipelineColorBlendState(const std::vector<ListObjectID<VkPipelineColorBlendAttachmentState>>& attachments, float blendConstantR, float blendConstantG, float blendConstantB, float blendConstantA);

		ListObjectID<VkViewport> AddPipelineViewport(float x, float y, uint32_t width, uint32_t height, float minDepth, float maxDepth);
		ListObjectID<VkRect2D> AddPipelineScissor(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height);
		ListObjectID<PipelineViewportsStateList> AddPipelineViewportState(const std::vector<std::pair<ListObjectID<VkViewport>, ListObjectID<VkRect2D>>>& viewportScissorPairs);

		ListObjectID<VkClearValue> AddClearColorValue(float r, float g, float b, float a);
		ListObjectID<VkClearValue> AddClearColorValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
		ListObjectID<VkClearValue> AddClearColorValue(int32_t r, int32_t g, int32_t b, int32_t a);

		ListObjectID<VkClearValue> AddClearDepthValue(float depth, uint32_t stencil);

		ShaderStageCreationData GetShaderStageCreationData(ListObjectID<ShaderStageCreationData> shaderDataID) const;
		VertexInputList GetVertexInputList(ListObjectID<VertexInputList> vertexInputID) const;

		VkPipelineInputAssemblyStateCreateInfo GetInputAssemblyState(ListObjectID<VkPipelineInputAssemblyStateCreateInfo> inputAssemblyID) const;
		PipelineViewportsStateList GetPipelineViewportsStateList(ListObjectID<PipelineViewportsStateList> vieportsStateID) const;

		VkViewport GetViewport(ListObjectID<VkViewport> viewportID) const;
		VkRect2D GetScissors(ListObjectID<VkRect2D> scissorsID) const;

		std::vector<VkClearValue> GetClearValues(const std::vector<ListObjectID<VkClearValue>>& clearValuesIDList) const;

		VkPipelineRasterizationStateCreateInfo GetPipelineRasterizationState(ListObjectID<VkPipelineRasterizationStateCreateInfo> rasterizationStateID) const;
		VkPipelineMultisampleStateCreateInfo GetPipelineMultisampleState(ListObjectID<VkPipelineMultisampleStateCreateInfo> multisamplingStateID) const;
		VkPipelineDepthStencilStateCreateInfo GetPipelineDepthStencilState(ListObjectID<VkPipelineDepthStencilStateCreateInfo> depthStencilStateID) const;

		ColorBlendSettings GetColorBlendSettings(ListObjectID<ColorBlendSettings> colorBlendSettingsID) const;

		std::vector<VkVertexInputBindingDescription> GetVertexInputBindingDescriptionsList(const std::vector<ListObjectID<VkVertexInputBindingDescription>>& vertexBindingsIDs) const;
		std::vector<VkVertexInputAttributeDescription> GetVertexInputAttributeDescriptionsList(const std::vector<ListObjectID<VkVertexInputAttributeDescription>>& vertexAttributesIDs) const;
		std::vector<VkPipelineColorBlendAttachmentState> GetPipelineColorBlendAttachmentStatesList(const std::vector<ListObjectID<VkPipelineColorBlendAttachmentState>>& pipelineColorBlendAttachmentIDs) const;
	};
}
