cmake_minimum_required(VERSION 3.5)  # You can adjust the required CMake version here
project(TCPIP C CXX)  # Set C and C++ as the languages for the project

# Set C and C++ standard (change to the version you want to use, e.g., 11, 14, 17, etc.)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Add your source files here (replace "main.cpp" with your actual source files)
set(SOURCES
    src/main.cpp
)

# Add header files if needed (replace "header.h" with your actual header files)
set(HEADERS
    #include/header.h
)

# Add any additional directories where headers or libraries are located
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add any external libraries if needed
# Example: find_package(OpenGL REQUIRED)
#          include_directories(${OpenGL_INCLUDE_DIRS})
#          target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARIES})

# Create the executable for your project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Optionally, you can specify compiler options if needed
# Example: target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

# Optionally, you can install your executable or libraries
# Example: install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Optionally, you can specify where to build the project (out-of-source build recommended)
# Example: set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
#          set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#          set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Optionally, you can add tests or subdirectories to organize your project
# Example: add_subdirectory(tests)

# Optionally, you can enable testing with CTest
# Example: enable_testing()

# Optionally, you can add custom targets or commands
# Example: add_custom_target(my_custom_target COMMAND ${CMAKE_COMMAND} ...)

# Optionally, you can add dependencies between targets or custom commands
# Example: add_dependencies(my_target dependency_target)

# Optionally, you can set additional properties for the project
# Example: set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Optionally, you can enable CMake's testing facilities
# Example: include(CTest)
#          add_test(NAME MyTest COMMAND MyTestCommand)

# Optionally, you can include other CMake files or packages
# Example: include(FindPackageHandleStandardArgs)
