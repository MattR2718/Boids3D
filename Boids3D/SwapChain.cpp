#include "Swapchain.h"

void SwapChain::create_swap_chain(GraphicsDevice& graphics_device, Surface& surface){
	auto surface_capabilities = graphics_device.physical_device.physical_device.getSurfaceCapabilitiesKHR(surface.surface);
	std::vector<vk::SurfaceFormatKHR> available_formats = graphics_device.physical_device.physical_device.getSurfaceFormatsKHR(surface.surface);
	std::vector<vk::PresentModeKHR> available_present_modes = graphics_device.physical_device.physical_device.getSurfacePresentModesKHR(surface.surface);

	surface_format = SwapChain::choose_swap_surface_format(available_formats);
	swap_chain_extent = choose_swap_extent(surface_capabilities, surface.p_window);
	auto min_image_count = std::max(3u, surface_capabilities.minImageCount);
	min_image_count = (surface_capabilities.maxImageCount > 0 && min_image_count > surface_capabilities.maxImageCount) ? surface_capabilities.maxImageCount : min_image_count;
	
	vk::SwapchainCreateInfoKHR swap_chain_create_info{
		.flags = vk::SwapchainCreateFlagsKHR(),
		.surface = surface.surface,
		.minImageCount = min_image_count,
		.imageFormat = surface_format.format,
		.imageColorSpace = surface_format.colorSpace,
		.imageExtent = swap_chain_extent,
		.imageArrayLayers = 1,												// Always 1 unless developing stereoscopic 3D app
		.imageUsage = vk::ImageUsageFlagBits::eColorAttachment,             // Specifies what kind of operation the images are used for (rendering to in this app => colour)
		.preTransform = surface_capabilities.currentTransform,
		.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
		.presentMode = choose_swap_present_mode(available_present_modes),
		.clipped = true,
		.oldSwapchain = VK_NULL_HANDLE
	};

	if (graphics_device.logical_device.queue_family_indices[0] == graphics_device.logical_device.queue_family_indices[1]) {
		swap_chain_create_info.imageSharingMode = vk::SharingMode::eExclusive;
		swap_chain_create_info.queueFamilyIndexCount = 0;
		swap_chain_create_info.pQueueFamilyIndices = nullptr;
	}
	else {
		swap_chain_create_info.imageSharingMode = vk::SharingMode::eConcurrent;
		swap_chain_create_info.queueFamilyIndexCount = 2;
		swap_chain_create_info.pQueueFamilyIndices = graphics_device.logical_device.queue_family_indices.data();
	}

	swap_chain = vk::raii::SwapchainKHR(graphics_device.logical_device.device, swap_chain_create_info);
	swap_chain_images = swap_chain.getImages();

}

void SwapChain::create_image_views(GraphicsDevice& graphics_device){
	swap_chain_image_views.clear();

	vk::ImageViewCreateInfo image_view_create_info{
		.viewType = vk::ImageViewType::e2D,
		.format = surface_format.format,
		.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 }
	};

	for (auto image : swap_chain_images) {
		image_view_create_info.image = image;
		swap_chain_image_views.emplace_back(graphics_device.logical_device.device, image_view_create_info);
	}
}

vk::SurfaceFormatKHR SwapChain::choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& available_formats){
	const auto formatIt = std::ranges::find_if(available_formats,
		[](const auto& format) {
			return format.format == vk::Format::eB8G8R8A8Srgb &&
				format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
		});
	return formatIt != available_formats.end() ? *formatIt : available_formats[0];
}


/*
There are four possible modes available in Vulkan:
	VK_PRESENT_MODE_IMMEDIATE_KHR: Images submitted by your application are transferred to the screen right away, which may result in tearing.

	VK_PRESENT_MODE_FIFO_KHR: The swap chain is a queue where the display takes an image from the front of the queue when the display is refreshed, 
							and the program inserts rendered images at the back of the queue. If the queue is full, then the program has to wait. 
							This is most similar to vertical sync as found in modern games. The moment that the display is refreshed is known 
							as "vertical blank".

	VK_PRESENT_MODE_FIFO_RELAXED_KHR: This mode only differs from the previous one if the application is late and the queue was empty at the 
							last vertical blank. Instead of waiting for the next vertical blank, 
							the image is transferred right away when it finally arrives. 
							This may result in visible tearing.

	VK_PRESENT_MODE_MAILBOX_KHR: This is another variation of the second mode. 
								Instead of blocking the application when the queue is full, the images that are already queued are simply 
								replaced with the newer ones. This mode can be used to render frames as fast as possible while still avoiding tearing, 
								resulting in fewer latency issues than standard vertical sync. 
								This is commonly known as "triple buffering," although the existence of three buffers alone does not 
								necessarily mean that the framerate is unlocked.


	Only VK_PRESENT_MODE_FIFO_KHR is guaranteed to be available so default to that, VK_PRESENT_MODE_MAILBOX_KHR is a nice tradeoff ie energy use is
	not a concern (e.g. on mobile devices), so use VK_PRESENT_MODE_MAILBOX_KHR if it is available.

*/
vk::PresentModeKHR SwapChain::choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& available_present_modes){
	for (const auto& available_mode : available_present_modes) {
		if (available_mode == vk::PresentModeKHR::eMailbox) {
			return available_mode;
		}
	}
	
	return vk::PresentModeKHR::eFifo;
}

/*
	Swap extent is the resolution of the swpa images and is almosty always the resolution of the window being drawn to.

	The resolution of the window requested at the start was in screen coordinates, Vulkan works in pixels.
	On some displays, e.g. Apple Retina Display, screen coordinates do not correspond to pixels.
	Therefore we need to get the glfwFrameBufferSize which is in pixels.

*/
vk::Extent2D SwapChain::choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window){
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	return {
		std::clamp<uint32_t>(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
		std::clamp<uint32_t>(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
	};
}
