#include "LogicalDevice.h"

void LogicalDevice::create_logical_device(PhysicalDevice& physical_device, vk::raii::SurfaceKHR& surface){
    // Find the index of the first queue family that supports graphics
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physical_device.physical_device.getQueueFamilyProperties();

    // get the first index into queueFamilyProperties which supports graphics
    auto graphicsQueueFamilyProperty = std::ranges::find_if(queueFamilyProperties, [](auto const& qfp)
        { return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0); });

    auto graphicsIndex = static_cast<uint32_t>(std::distance(queueFamilyProperties.begin(), graphicsQueueFamilyProperty));

    // determine a queueFamilyIndex that supports present
    // first check if the graphicsIndex is good enough
    auto presentIndex = physical_device.physical_device.getSurfaceSupportKHR(graphicsIndex, *surface)
        ? graphicsIndex
        : static_cast<uint32_t>(queueFamilyProperties.size());
    if (presentIndex == queueFamilyProperties.size())
    {
        // the graphicsIndex doesn't support present -> look for another family index that supports both
        // graphics and present
        for (size_t i = 0; i < queueFamilyProperties.size(); i++)
        {
            if ((queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) &&
                physical_device.physical_device.getSurfaceSupportKHR(static_cast<uint32_t>(i), *surface))
            {
                graphicsIndex = static_cast<uint32_t>(i);
                presentIndex = graphicsIndex;
                break;
            }
        }
        if (presentIndex == queueFamilyProperties.size())
        {
            // there's nothing like a single family index that supports both graphics and present -> look for another
            // family index that supports present
            for (size_t i = 0; i < queueFamilyProperties.size(); i++)
            {
                if (physical_device.physical_device.getSurfaceSupportKHR(static_cast<uint32_t>(i), *surface))
                {
                    presentIndex = static_cast<uint32_t>(i);
                    break;
                }
            }
        }
    }
    if ((graphicsIndex == queueFamilyProperties.size()) || (presentIndex == queueFamilyProperties.size()))
    {
        throw std::runtime_error("ERROR [LogicalDevice::create_logical_device]: Could not find a queue for either graphics or present");
    }

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
    //vk::DeviceQueueCreateInfo deviceQueueCreateInfo{ .queueFamilyIndex = graphicsIndex, .queueCount = 1, .pQueuePriorities = &queuePriority };

    std::vector<vk::DeviceQueueCreateInfo> queueInfos;
    queueInfos.push_back({ .queueFamilyIndex = graphicsIndex, .queueCount = 1, .pQueuePriorities = &queuePriority });
    if (presentIndex != graphicsIndex) {
        queueInfos.push_back({ .queueFamilyIndex = presentIndex, .queueCount = 1, .pQueuePriorities = &queuePriority });
    }

    vk::DeviceCreateInfo deviceCreateInfo{ .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
                                           .queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size()),
                                           .pQueueCreateInfos = queueInfos.data(),
                                           .enabledExtensionCount = static_cast<uint32_t>(physical_device.deviceExtensions.size()),
                                           .ppEnabledExtensionNames = physical_device.deviceExtensions.data() };

    device = vk::raii::Device(physical_device.physical_device, deviceCreateInfo);
    graphics_queue = vk::raii::Queue(device, graphicsIndex, 0);
    present_queue = vk::raii::Queue(device, presentIndex, 0);
}
