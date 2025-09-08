#include "CommandBuffer.h"

void CommandBuffer::create_command_pool(const GraphicsDevice& graphics_device){
	vk::CommandPoolCreateInfo pool_info{
		.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
		.queueFamilyIndex = graphics_device.logical_device.queue_family_indices[0]
	};

	command_pool = vk::raii::CommandPool(graphics_device.logical_device.device, pool_info);
}

void CommandBuffer::create_command_buffer(const GraphicsDevice& graphics_device){
	vk::CommandBufferAllocateInfo alloc_info{
		.commandPool = command_pool,
		.level = vk::CommandBufferLevel::ePrimary,
		.commandBufferCount = 1
	};

	command_buffer = std::move(vk::raii::CommandBuffers(graphics_device.logical_device.device, alloc_info).front());
}

void CommandBuffer::record_command_buffer(const GraphicsDevice& graphics_device, const SwapChain& swap_chain, uint32_t imageIndex, const Scene* scene){
	command_buffer.begin({});

	// Before rendering starts, transision swapchain image to COLOR_ATTACHMENT_OPTIMAL
	transition_image_layout(
		imageIndex,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eColorAttachmentOptimal,
		{},
		vk::AccessFlagBits2::eColorAttachmentWrite,
		vk::PipelineStageFlagBits2::eTopOfPipe,
		vk::PipelineStageFlagBits2::eColorAttachmentOutput,
		swap_chain
	);

	vk::ClearColorValue clear_colour_val(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f});

	vk::RenderingAttachmentInfo attachment_info = {
		.imageView = swap_chain.swap_chain_image_views[imageIndex],
		.imageLayout = vk::ImageLayout::eColorAttachmentOptimal,
		.loadOp = vk::AttachmentLoadOp::eClear,
		.storeOp = vk::AttachmentStoreOp::eStore,
		.clearValue = clear_colour_val
	};

	vk::RenderingInfo rendering_info = {
		.renderArea = { .offset = {0, 0}, .extent = swap_chain.swap_chain_extent },
		.layerCount = 1,
		.colorAttachmentCount = 1,
		.pColorAttachments = &attachment_info
	};

	command_buffer.beginRendering(rendering_info);


	for (const auto& render_object : (*scene).render_objects) {
		command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, render_object->material->pipeline.graphics_pipeline);
		command_buffer.setViewport(0, vk::Viewport(0.0f, 0.0f, static_cast<float>(swap_chain.swap_chain_extent.width), static_cast<float>(swap_chain.swap_chain_extent.height), 0.0f, 1.0f));
		command_buffer.setScissor(0, vk::Rect2D(vk::Offset2D(0, 0), swap_chain.swap_chain_extent));
		command_buffer.draw(3, 1, 0, 0);
	}

	command_buffer.endRendering();

	// After rendering, transition the swapchain image to PRESENT_SRC
	transition_image_layout(
		imageIndex,
		vk::ImageLayout::eColorAttachmentOptimal,
		vk::ImageLayout::ePresentSrcKHR,
		vk::AccessFlagBits2::eColorAttachmentWrite,                 // srcAccessMask
		{},                                                      // dstAccessMask
		vk::PipelineStageFlagBits2::eColorAttachmentOutput,        // srcStage
		vk::PipelineStageFlagBits2::eBottomOfPipe,                  // dstStage
		swap_chain
	);
	
	command_buffer.end();
}

void CommandBuffer::transition_image_layout(uint32_t imageIndex, 
											vk::ImageLayout oldLayout, 
											vk::ImageLayout newLayout, 
											vk::AccessFlags2 srcAccessMask, 
											vk::AccessFlags2 dstAccessMask, 
											vk::PipelineStageFlags2 srcStageMask, 
											vk::PipelineStageFlags2 dstStageMask,
											const SwapChain& swap_chain)
{
	vk::ImageMemoryBarrier2 barrier = {
		.srcStageMask = srcStageMask,
		.srcAccessMask = srcAccessMask,
		.dstStageMask = dstStageMask,
		.dstAccessMask = dstAccessMask,
		.oldLayout = oldLayout,
		.newLayout = newLayout,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = swap_chain.swap_chain_images[imageIndex],
		.subresourceRange = {
			.aspectMask = vk::ImageAspectFlagBits::eColor,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	vk::DependencyInfo dependency_info{
		.dependencyFlags = {},
		.imageMemoryBarrierCount = 1,
		.pImageMemoryBarriers = &barrier
	};

	command_buffer.pipelineBarrier2(dependency_info);
}
