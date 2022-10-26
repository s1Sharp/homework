cmake_minimum_required(VERSION 3.9.1)
project(MPI)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -o3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(EXE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/executable")
set(EXECUTABLE_OUTPUT_PATH  ${EXE_DIR})
# OpenMP & MPI
find_package(OpenMP)
find_package(MPI)


set(UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/utils")

include_directories(${PROJECT_NAME} ${MPI_INCLUDE_PATH} ${UTILS_DIR} ${MSMPI_INC})
message(STATUS "Source files: ${MPI_INCLUDE_PATH}")

function(SETEXEMPI REQUIRED_ARG)
    add_executable("${PROJECT_NAME}_${REQUIRED_ARG}" ${REQUIRED_ARG}.cpp)
    target_link_libraries("${PROJECT_NAME}_${REQUIRED_ARG}" PUBLIC MPI::MPI_CXX)
endfunction()


################################
# start executables
################################

setexempi(task1)
setexempi(task2)
setexempi(task3)
setexempi(task4)
setexempi(task5)
setexempi(task6)
set_target_properties(MPI_task6 PROPERTIES LINK_FLAGS -Wl, --stack, /STACK:10000000)
setexempi(task7)
setexempi(task8)