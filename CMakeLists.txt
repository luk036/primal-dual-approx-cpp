# Distributed under the MIT License (See accompanying file /LICENSE )

# CMake build : global project

cmake_minimum_required (VERSION 3.8.2)

# set(CMAKE_PREFIX_PATH $ENV{CONDA_PREFIX})

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project (PrimalDualApproxCpp LANGUAGES CXX)

option(ENABLE_COVERAGE "Generates the coverage build" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." OFF)

include(CTest) # Must be called before adding tests but after calling project(). This automatically calls enable_testing() and configures ctest targets when using Make/Ninja
include(CMakeDependentOption)# This is a really useful scripts that creates options that depends on other options. It can even be used with generator expressions !

# Custom modules and scripts

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Colors)
include(Doctest)
include(LTO)
include(Warnings)
include(CopyDllsForDebug)

# Guard against in-source builds and bad build-type strings
#
include(ConfigSafeGuards)

###############
##  OPTIONS  ##
###############

# You should try to give as much control over the project setup to the user.
# When modifying compile flags for example, if they are not mandatory, provide an option.

# Use your own option for tests, in case people use your library through add_subdirectory
cmake_dependent_option(BP_BUILD_TESTS
    "Enable Boilerplate project tests targets" ON # By default we want tests if CTest is enabled
    "BUILD_TESTING" OFF # Stay coherent with CTest variables
)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    add_compile_options(/std:c++latest /W3 /WX )
else()
    add_compile_options(-DBOOST_EXCEPTION_DISABLE -Wall -Wnon-virtual-dtor -Wunused -pedantic)
endif()

# set(LIBS ${LIBS} "-L$ENV{CONDA_PREFIX}/lib")

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)
find_package (fmt REQUIRED)
# find_package (spdlog REQUIRED)

# set (Boost_DIR $ENV{CONDA_PREFIX}/include)
find_package (Boost REQUIRED COMPONENTS coroutine context system)
if (Boost_FOUND)
    message(STATUS "Found boost: ${Boost_INCLUDE_DIRS}")
    set(LIBS ${LIBS} ${Boost_LIBRARIES})
endif (Boost_FOUND)

set (LIBRARY_INCLUDE_PATH  ${LIBRARY_INCLUDE_PATH} ${Boost_INCLUDE_DIRS})

add_subdirectory (external EXCLUDE_FROM_ALL)

# Enable code coverage with -DENABLE_COVERAGE=1
# if(ENABLE_COVERAGE)
#     set(CMAKE_BUILD_TYPE "Coverage")
#     include(CodeCoverage)
#     setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_NAME}_test coverage)
# endif()

# add_subdirectory (doc)
add_subdirectory (lib)
add_subdirectory (app)

enable_testing ()
