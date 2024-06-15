# CMakeList.txt : CMake project for ElevatorSimulator, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Controller "controller.cpp" "elevator.h" "state.h" "state.cpp" "elevator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Controller PROPERTY CXX_STANDARD 20)
endif()
