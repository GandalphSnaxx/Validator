cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Validator VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
# include_directories(include)
include_directories(include Libraries/FlagField/include)

# Add the source files
set(SOURCES
    # src/config_t.cpp
    # src/helper_funcs.cpp
    # src/keyed_data_t.cpp
    # src/keyed_list_t.cpp
    # src/range_t.cpp
    src/return_t.cpp
    # src/valid_list_t.cpp
)

# Add the executable for the tests
add_executable(ValidatorTests
    tests/main.cpp
    ${SOURCES}
)

# Enable debug messages
target_compile_definitions(ValidatorTests PRIVATE DEBUG)