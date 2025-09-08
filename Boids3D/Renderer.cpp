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
	while (vk::Result::eTimeout == graphics_device.logical_device.device.waitForFences(*in_flight_fences[current_frame], vk::True, UINT64_MAX));
	//graphics_device.logical_device.device.waitIdle();

	// Grab an image from the framebuffer after the previous frame has finished
	auto [result, image_index] = swap_chain.swap_chain.acquireNextImage(UINT64_MAX, *present_complete_semaphores[current_frame], nullptr);

	graphics_device.logical_device.device.resetFences(*in_flight_fences[current_frame]);
	command_buffer.command_buffers[current_frame].reset();

	command_buffer.record_command_buffer(graphics_device, swap_chain, image_index, current_frame, scene);
	vk::PipelineStageFlags wait_destination_stage_mask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	vk::SubmitInfo submit_info{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &*present_complete_semaphores[current_frame],
		.pWaitDstStageMask = &wait_destination_stage_mask,
		.commandBufferCount = 1,
		.pCommandBuffers = &*command_buffer.command_buffers[current_frame],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &*render_finished_semaphores[image_index]
	};

	graphics_device.logical_device.graphics_queue.submit(submit_info, *in_flight_fences[current_frame]);

	const vk::PresentInfoKHR present_info_khr{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &*render_finished_semaphores[image_index],
		.swapchainCount = 1,
		.pSwapchains = &*swap_chain.swap_chain,
		.pImageIndices = &image_index
	};

	result = graphics_device.logical_device.graphics_queue.presentKHR(present_info_khr);

	current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;

	switch (result){
		case vk::Result::eSuccess: break;
		case vk::Result::eSuboptimalKHR: std::println(stderr, "ERROR [Renderer::draw_frame]: vk::Queue::presentKHR returned vk::Result::eSuboptimalKHR !\n"); break;
		default: break;  // an unexpected result is returned!
	}
}

void Renderer::create_sync_objects(const GraphicsDevice& graphics_device) {
	present_complete_semaphores.clear();
	render_finished_semaphores.clear();
	in_flight_fences.clear();

	for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		present_complete_semaphores.emplace_back(graphics_device.logical_device.device, vk::SemaphoreCreateInfo());
		in_flight_fences.emplace_back(vk::raii::Fence(graphics_device.logical_device.device, { .flags = vk::FenceCreateFlagBits::eSignaled }));

	}

	for (int i = 0; i < swap_chain.swap_chain_images.size(); i++) {
		render_finished_semaphores.emplace_back(graphics_device.logical_device.device, vk::SemaphoreCreateInfo());
	}
}
