#include "Renderer.h"


void Renderer::set_window_ptr(GLFWwindow* window){
	surface.p_window = window;
}

void Renderer::init_renderer(){
	graphics_device.init_graphics_device(surface);
	swap_chain.create_swap_chain(graphics_device, surface);
	swap_chain.create_image_views(graphics_device);
}

void Renderer::draw_frame(const Scene* scene){
	graphics_device.logical_device.device.waitIdle();

	// Grab an image from the framebuffer after the previous frame has finished
	auto [result, image_index] = swap_chain.swap_chain.acquireNextImage(UINT64_MAX, *present_complete_semaphore, nullptr);
	command_buffer.record_command_buffer(graphics_device, swap_chain, image_index, scene);
	graphics_device.logical_device.device.resetFences(*draw_fence);
	vk::PipelineStageFlags wait_destination_stage_mask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	vk::SubmitInfo submit_info{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &*present_complete_semaphore,
		.pWaitDstStageMask = &wait_destination_stage_mask,
		.commandBufferCount = 1,
		.pCommandBuffers = &*command_buffer.command_buffer,
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &*render_finished_semaphore
	};

	graphics_device.logical_device.graphics_queue.submit(submit_info, *draw_fence);

	while (vk::Result::eTimeout == graphics_device.logical_device.device.waitForFences(*draw_fence, vk::True, UINT64_MAX));

	const vk::PresentInfoKHR present_info_khr{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &*render_finished_semaphore,
		.swapchainCount = 1,
		.pSwapchains = &*swap_chain.swap_chain,
		.pImageIndices = &image_index
	};

	result = graphics_device.logical_device.graphics_queue.presentKHR(present_info_khr);
	switch (result){
		case vk::Result::eSuccess: break;
		case vk::Result::eSuboptimalKHR: std::println(stderr, "ERROR [Renderer::draw_frame]: vk::Queue::presentKHR returned vk::Result::eSuboptimalKHR !\n"); break;
		default: break;  // an unexpected result is returned!
	}
}

void Renderer::create_sync_objects(const GraphicsDevice& graphics_device){
	present_complete_semaphore = vk::raii::Semaphore(graphics_device.logical_device.device, vk::SemaphoreCreateInfo());
	render_finished_semaphore = vk::raii::Semaphore(graphics_device.logical_device.device, vk::SemaphoreCreateInfo());
	draw_fence = vk::raii::Fence(graphics_device.logical_device.device, { .flags = vk::FenceCreateFlagBits::eSignaled });
}
