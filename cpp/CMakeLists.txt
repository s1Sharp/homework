cmake_minimum_required (VERSION 3.8)
project(cpp_homework VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

################################
# build type
################################

# Set a default build type if not passed
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release")
endif()

################################
# src
################################

file(GLOB_RECURSE SOURCES src/**.cpp)
file(GLOB_RECURSE HEADERS src/**.h src/**.hpp)

# add_executable(${PROJECT_NAME}
#   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
#   ${SOURCES}
#   ${HEADERS}
# )

set(GLOBAL_LINK_LIB         

)

################################
# remove main.cpp for hometask -> test should work
################################

set (EXCLUDE_MAIN "main.cpp")
foreach (TMP_PATH ${SOURCES})
    string (FIND ${TMP_PATH} ${EXCLUDE_MAIN} EXCLUDE_MAIN_FOUND)
    if (NOT ${EXCLUDE_MAIN_FOUND} EQUAL -1)
        list (REMOVE_ITEM SOURCES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

function(SETEXE REQUIRED_ARG)
    file(GLOB_RECURSE SOURCES${REQUIRED_ARG} src/task${REQUIRED_ARG}/**.cpp)
    file(GLOB_RECURSE HEADERS${REQUIRED_ARG} src/task${REQUIRED_ARG}/**.h src/task${REQUIRED_ARG}/**.hpp)
    message(STATUS "Source files: ${SOURCES${REQUIRED_ARG}}")
    add_executable(${PROJECT_NAME}${REQUIRED_ARG}  ${SOURCES${REQUIRED_ARG}})
    target_include_directories(${PROJECT_NAME}${REQUIRED_ARG} PRIVATE ${HEADERS${REQUIRED_ARG}})
    target_link_libraries(${PROJECT_NAME}${REQUIRED_ARG}  ${GLOBAL_LINK_LIB})
endfunction()

################################
# start executables
################################

setexe("1309")
setexe("1909")

################################
# end executables
################################

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src  FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src  FILES ${HEADERS})

################################
# GTest
################################

file(GLOB_RECURSE TEST_SOURCES test/**.cpp)
file(GLOB_RECURSE TEST_HEADERS test/**.h)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  Google_Tests_run
  ${TEST_SOURCES}
  ${TEST_HEADERS}
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Google_Tests_run PRIVATE  
  ${CMAKE_CURRENT_SOURCE_DIR}/src 
  ${CMAKE_CURRENT_SOURCE_DIR}/test
)

target_link_libraries(
  Google_Tests_run
  GTest::gtest
  GTest::gmock
  GTest::gtest_main
  GTest::gmock_main
  ${GLOBAL_LINK_LIB}
)

include(GoogleTest)
gtest_discover_tests(Google_Tests_run)
