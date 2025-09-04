# CMakeList.txt : CMake project for Boids3D, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Boids3D "Boids3D.cpp" "Boids3D.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Boids3D PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
