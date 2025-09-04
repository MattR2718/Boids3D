#include "PhysicalDevice.h"

void PhysicalDevice::pick_physical_device(vk::raii::Instance* instance){
    std::vector<vk::raii::PhysicalDevice> devices = (*instance).enumeratePhysicalDevices();
    const auto devIter = std::ranges::find_if(devices,
        [&](auto const& device) {
            // Make sure supports Vulkan 1.3
            bool isSuitable = device.getProperties().apiVersion >= VK_API_VERSION_1_3;

            // Check for queue families
            auto queueFamilies = device.getQueueFamilyProperties();
            bool supportsGraphics = std::ranges::any_of(queueFamilies, [](auto const& qfp) { return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });
            isSuitable = isSuitable && supportsGraphics;

            // Check that device supports all required device extensions
            auto extensions = device.enumerateDeviceExtensionProperties();

            // Check that device supports the required device extensions
            bool supportsAllRequiredExtensions = std::ranges::all_of(deviceExtensions, [&extensions](auto const& requiredDeviceExtension) {
                return std::ranges::any_of(extensions, [requiredDeviceExtension](auto const& availableDeviceExtension) {
                    return strcmp(availableDeviceExtension.extensionName, requiredDeviceExtension) == 0;
                    });
                });
            isSuitable = isSuitable && supportsAllRequiredExtensions;


            // Check that device supports required features from Vulkan 1.3
            auto features = device.template getFeatures2<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();
            bool supportsRequiredFeatures = features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
                features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

            isSuitable = isSuitable && supportsRequiredFeatures;

            return isSuitable;
        });

    if (devIter != devices.end()) {
        physical_device = *devIter;
        std::println("Using GPU: {}", std::string(physical_device.getProperties().deviceName.data()));
    }else{
        throw std::runtime_error("ERROR [PhysicalDevice::pick_physical_device]: Failed to find a suitable GPU");
    }
}

uint32_t PhysicalDevice::find_queue_families(VkPhysicalDevice device){
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physical_device.getQueueFamilyProperties();

    // Get the first index into queueFamilyProperties which supports graphics
    auto graphicsQueueFamilyProperty =
        std::find_if(queueFamilyProperties.begin(),
            queueFamilyProperties.end(),
            [](vk::QueueFamilyProperties const& qfp) { return qfp.queueFlags & vk::QueueFlagBits::eGraphics; });

    return static_cast<uint32_t>(std::distance(queueFamilyProperties.begin(), graphicsQueueFamilyProperty));
}
