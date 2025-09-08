#pragma once

#include "VulkanInclude.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"
#include "Scene.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

class CommandBuffer {
public:
	vk::raii::CommandPool command_pool = nullptr;
	std::vector<vk::raii::CommandBuffer> command_buffers;


	void create_command_pool(const GraphicsDevice& graphics_device);
	void create_command_buffers(const GraphicsDevice& graphics_device);
	void record_command_buffer(const GraphicsDevice& graphics_device, const SwapChain& swap_chain, uint32_t imageIndex, uint32_t current_frame, const Scene* scene);

private:

	void transition_image_layout(uint32_t imageIndex,
		vk::ImageLayout oldLayout,
		vk::ImageLayout newLayout,
		vk::AccessFlags2 srcAccessMask,
		vk::AccessFlags2 dstAccessMask,
		vk::PipelineStageFlags2 srcStageMask,
		vk::PipelineStageFlags2 dstStageMask,
		const SwapChain& swap_chain,
		const uint32_t current_frame);

};