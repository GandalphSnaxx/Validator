cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Validator VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include Libraries/FlagField/include)

# Add the source files
set(SOURCES src/return_t.cpp)

# Create a library target
add_library(Validator STATIC ${SOURCES})

# Add the executable for the tests
add_executable(ValidatorTests tests/main.cpp)

# Link the library to the test executable
target_link_libraries(ValidatorTests PRIVATE Validator)

# Enable debug messages
target_compile_definitions(ValidatorTests PRIVATE DEBUG)