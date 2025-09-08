#pragma once

#include "VulkanInclude.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"
#include "Scene.h"

class CommandBuffer {
public:
	vk::raii::CommandPool command_pool = nullptr;
	vk::raii::CommandBuffer command_buffer = nullptr;


	void create_command_pool(const GraphicsDevice& graphics_device);
	void create_command_buffer(const GraphicsDevice& graphics_device);
	void record_command_buffer(const GraphicsDevice& graphics_device, const SwapChain& swap_chain, uint32_t imageIndex, const Scene* scene);

private:

	void transition_image_layout(uint32_t imageIndex,
		vk::ImageLayout oldLayout,
		vk::ImageLayout newLayout,
		vk::AccessFlags2 srcAccessMask,
		vk::AccessFlags2 dstAccessMask,
		vk::PipelineStageFlags2 srcStageMask,
		vk::PipelineStageFlags2 dstStageMask,
		const SwapChain& swap_chain);

};