#include "Pipeline.h"

void Pipeline::create_graphics_pipeline(const GraphicsDevice& graphics_device, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename){
	vk::raii::ShaderModule vertex_shader_module = Shader::create_shader_module(graphics_device, vertex_shader_filename);
	vk::raii::ShaderModule fragment_shader_module = Shader::create_shader_module(graphics_device, fragment_shader_filename);

	vk::PipelineShaderStageCreateInfo vert_shader_stage_info{ .stage = vk::ShaderStageFlagBits::eVertex, .module = vertex_shader_module, .pName = "vertMain" };
	vk::PipelineShaderStageCreateInfo frag_shader_stage_info{ .stage = vk::ShaderStageFlagBits::eFragment, .module = fragment_shader_module, .pName = "fragMain"};

	vk::PipelineShaderStageCreateInfo shader_stages[] = { vert_shader_stage_info, frag_shader_stage_info };

	vk::PipelineVertexInputStateCreateInfo vertex_input_info;

	/*
		VK_PRIMITIVE_TOPOLOGY_POINT_LIST: points from vertices

		VK_PRIMITIVE_TOPOLOGY_LINE_LIST: line from every two vertices without reuse

		VK_PRIMITIVE_TOPOLOGY_LINE_STRIP: the end vertex of every line is used as start vertex for the next line

		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST: triangle from every three vertices without reuse

		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP: the second and third vertex of every triangle is used as first two vertices of the next triangle

		If you set the primitiveRestartEnable member to VK_TRUE, then it’s possible to break up lines and triangles in the _STRIP topology modes by using a special index of 0xFFFF or 0xFFFFFFFF.
	*/
	vk::PipelineInputAssemblyStateCreateInfo input_assembly{ .topology = vk::PrimitiveTopology::eTriangleList };

	std::vector<vk::DynamicState> dynamic_states = {
		vk::DynamicState::eViewport,
		vk::DynamicState::eScissor
	};

	vk::PipelineDynamicStateCreateInfo dynamic_state{ .dynamicStateCount = static_cast<uint32_t>(dynamic_states.size()), .pDynamicStates = dynamic_states.data() };

	vk::PipelineViewportStateCreateInfo viewport_state{ .viewportCount = 1, .scissorCount = 1 };

	vk::PipelineRasterizationStateCreateInfo rasterizer{
		.depthClampEnable = vk::False,				// If set to VK_TRUE, fragments that are beyond the near and far planes are clamped to them as opposed to 
													//discarding them. Requires enabling a GPU feature
		.rasterizerDiscardEnable = vk::False,		// If set to VK_TRUE, geometry does not pass through rasterizer stage, basically disables output to framebuffer
		.polygonMode = vk::PolygonMode::eFill,		// Determines how fragments are generated for geometry:
													// VK_POLYGON_MODE_FILL: fill the area of the polygon with fragments
													// VK_POLYGON_MODE_LINE: polygon edges are drawn as lines
													// VK_POLYGON_MODE_POINT: polygon vertices are drawn as points
													// Using any mode other than fill requires enabling a GPU feature.
		.cullMode = vk::CullModeFlagBits::eBack,    // Determines what, if any faces are culled
		.frontFace = vk::FrontFace::eClockwise,		// Determines vertex order of the faces to be considered front
		.depthBiasEnable = vk::False,				// Can alter the depth values by adding a constant value or biasing them based on a fragments slope
		.depthBiasSlopeFactor = 1.0f,				// \ Sometimes used for shadow mapping
		.lineWidth = 1.0f							// Thickness of lines in terms of fragments
													// Maximum width supported depends on hardware
													// Any thicker than 1.0f requires the "wideLines" GPU feature
	};

	// Enabling requires GPU feature
	vk::PipelineMultisampleStateCreateInfo multisampling{
		.rasterizationSamples = vk::SampleCountFlagBits::e1,
		.sampleShadingEnable = vk::False
	};

	// Two ways of colour blending
	//	Mix the old and the new value to produce a fuinal colour
	//	COmbine the old and new value using bitwise operation
	// If blandEnable is set to VK_FALSE, the new color from the fragment shader is passed through unmodified
	vk::PipelineColorBlendAttachmentState colour_blend_attachment;
	colour_blend_attachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
	colour_blend_attachment.blendEnable = vk::False;

	vk::PipelineColorBlendStateCreateInfo colour_blending{
		.logicOpEnable = vk::False,
		.logicOp = vk::LogicOp::eCopy,
		.attachmentCount = 1,
		.pAttachments = &colour_blend_attachment
	};

	/*
	
		You can use uniform values in shaders, which are globals similar to dynamic state variables that can be changed at drawing time to 
			alter the behavior of your shaders without having to recreate them. They are commonly used to pass the transformation matrix to the vertex shader, 
			or to create texture samplers in the fragment shader.

		These uniform values need to be specified during pipeline creation by creating a VkPipelineLayout object.
	
	*/

	vk::PipelineLayoutCreateInfo pipeline_layout_info{
		.setLayoutCount = 0,
		.pushConstantRangeCount = 0
	};

	pipeline_layout = vk::raii::PipelineLayout(graphics_device.logical_device.device, pipeline_layout_info);
}
