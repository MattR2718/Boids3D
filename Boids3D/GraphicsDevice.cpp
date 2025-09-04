#include "GraphicsDevice.h"

void GraphicsDevice::init_graphics_device(){
	vulkan_instance.create_instance();
	vulkan_instance.setup_debug_messenger();
}
