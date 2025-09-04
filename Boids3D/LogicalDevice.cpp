#include "LogicalDevice.h"

void LogicalDevice::create_logical_device(PhysicalDevice& physical_device){
    // Find the index of the first queue family that supports graphics
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physical_device.physical_device.getQueueFamilyProperties();

    // Get the first index into queueFamilyProperties which supports graphics
    auto graphicsQueueFamilyProperty = std::ranges::find_if(queueFamilyProperties, [](auto const& qfp)
        { return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0); });
    assert(graphicsQueueFamilyProperty != queueFamilyProperties.end() && "No graphics queue family found!");

    auto graphicsIndex = static_cast<uint32_t>(std::distance(queueFamilyProperties.begin(), graphicsQueueFamilyProperty));

    // Query for Vulkan 1.3 features
    /*
        In Vulkan, features are organized into different structures based on when they were introduced or what functionality they relate to. 
        For example: 
        - Basic features are in vk::PhysicalDeviceFeatures 
        - Vulkan 1.3 features are in vk::PhysicalDeviceVulkan13Features
        - Extension-specific features are in their own structures (like vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT)

        To enable multiple sets of features, Vulkan uses a concept called "structure chaining." 
        Each feature structure has a pNext field that can point to another structure, creating a chain of feature requests.
    */
    vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT> featureChain = {
        {},                               // vk::PhysicalDeviceFeatures2
        {.dynamicRendering = true },      // vk::PhysicalDeviceVulkan13Features
        {.extendedDynamicState = true }   // vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
    };

    // create a Device
    float queuePriority = 0.0f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo{ .queueFamilyIndex = graphicsIndex, .queueCount = 1, .pQueuePriorities = &queuePriority };
    vk::DeviceCreateInfo deviceCreateInfo{ .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
                                           .queueCreateInfoCount = 1,
                                           .pQueueCreateInfos = &deviceQueueCreateInfo,
                                           .enabledExtensionCount = static_cast<uint32_t>(physical_device.deviceExtensions.size()),
                                           .ppEnabledExtensionNames = physical_device.deviceExtensions.data() };

    device = vk::raii::Device(physical_device.physical_device, deviceCreateInfo);
    graphics_queue = vk::raii::Queue(device, graphicsIndex, 0);
}
