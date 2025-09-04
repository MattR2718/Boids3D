#include "GraphicsDevice.h"

void GraphicsDevice::init_graphics_device(Window& window){
	vulkan_instance.create_instance();
	vulkan_instance.setup_debug_messenger();
	window.create_surface(vulkan_instance.instance);
	physical_device.pick_physical_device(vulkan_instance.instance);
	logical_device.create_logical_device(physical_device, window.surface);
}
