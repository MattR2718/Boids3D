# CMakeList.txt : CMake project for Boids3D, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Boids3D "Boids3D.cpp" "Boids3D.h" 
                        "Application.cpp"
                        "Application.h"
                        "Window.cpp"
                        "Window.h"
                        "VulkanInstance.cpp"
                        "VulkanInstance.h"
                        "GraphicsDevice.cpp"
                        "GraphicsDevice.h"
                        "PhysicalDevice.cpp"
                        "PhysicalDevice.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Boids3D PROPERTY CXX_STANDARD 23)
endif()

include(FetchContent)

find_package (Vulkan REQUIRED)

#
#
#
#
# Fetch glfw
find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
    message(STATUS "GLFW not found. Fetching it with FetchContent...")

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
    )
    FetchContent_MakeAvailable(glfw)
endif()


#
#
#
#
#
# Fetch glm
find_package(glm QUIET)
if (NOT glm_FOUND)
    message(STATUS "GLM not found. Fetching it with FetchContent...")

    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        0.9.9.8 # pick a stable release, adjust as needed
    )

    # Ensure GLM is available
    FetchContent_MakeAvailable(glm)
endif()



#
#
#
#
#
# Fetch stb
find_package(Stb QUIET)
if (NOT STB_INCLUDE_DIRS)
    message(STATUS "stb not found. Fetching it with FetchContent...")

    FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG        master
    )

    FetchContent_GetProperties(stb)
    if (NOT stb_POPULATED)
        FetchContent_Populate(stb)
        set(STB_INCLUDE_DIRS ${stb_SOURCE_DIR})
    endif()
endif()



#
#
#
#
#
# Fetch tinyobjloader
find_package(tinyobjloader QUIET)

if (NOT tinyobjloader_FOUND)
    message(STATUS "tinyobjloader not found. Fetching it with FetchContent...")

    FetchContent_Declare(
        tinyobjloader
        GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
        GIT_TAG        v2.0.0rc10 # pick a stable release, adjust as needed
    )

    FetchContent_MakeAvailable(tinyobjloader)
endif()


target_link_libraries(Boids3D Vulkan::Vulkan glfw glm tinyobjloader)
target_include_directories(Boids3D PRIVATE ${STB_INCLUDE_DIRS})