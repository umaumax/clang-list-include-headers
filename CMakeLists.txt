# FYI
# [c\+\+ \- Cmake and clang tooling linking error \(outside of source tree\) \- Stack Overflow]( https://stackoverflow.com/questions/25782537/cmake-and-clang-tooling-linking-error-outside-of-source-tree )
# [libclang\-ffi CMakeLists\.txt · GitHub]( https://gist.github.com/take-cheeze/6806916 )
cmake_minimum_required(VERSION 2.8.8)
project(clang-list-include-headers)

set(CMAKE_CXX_COMPILER clang++)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# find_program(LLVM_CONFIG "llvm-config")
# if(NOT EXISTS "${LLVM_CONFIG}")
#   message(SEND_ERROR "llvm not found")
# endif()
# execute_process(COMMAND "${LLVM_CONFIG}" "--includedir"
#                 OUTPUT_VARIABLE LLVM_INCLUDE_DIR
#                 OUTPUT_STRIP_TRAILING_WHITESPACE)

set(SOURCES "clang-list-include-headers.cpp")

# Set the compile flags.
include_directories(${LLVM_INCLUDE_DIRS} ".")
add_definitions(${LLVM_DEFINITIONS})

# add pch files
file(GLOB PCH_FILES *.pch)
set(INCLUDE_PCH_FILES "")
foreach(PCH_FILE IN LISTS PCH_FILES)
  list(APPEND INCLUDE_PCH_FILES ${PCH_FILE})
endforeach(PCH_FILE)
set(INCLUDE_PCH_OPT "")
foreach(INCLUDE_PCH_FILE IN LISTS INCLUDE_PCH_FILES)
  list(APPEND INCLUDE_PCH_OPT "-include-pch ${INCLUDE_PCH_FILE}")
endforeach(INCLUDE_PCH_FILE)

set(CMAKE_CXX_FLAGS "-std=c++11 ${INCLUDE_PCH_OPT}")
message(STATUS ${CMAKE_SHARED_LINKER_FLAGS})

# Find the libraries that correspond to the LLVM components that we wish to use
# $ llvm-config --ldflags --libs --system-libs
# -L/usr/lib/llvm-5.0/lib
# -lLLVM-5.0
# TODO: この5.0表記を改善

# llvm_map_components_to_libnames(LLVM_LIBS -5.0)
set(LLVM_LIBS "LLVM")

# Link against LLVM libraries

# -L

link_directories(${LLVM_LIBRARY_DIRS})

# Now build our tools
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
                      ${LLVM_LIBS}
                      "clang"
                      "clangAST"
                      "clangASTMatchers"
                      "clangAnalysis"
                      "clangBasic"
                      "clangDriver"
                      "clangEdit"
                      "clangFrontend"
                      "clangFrontendTool"
                      "clangLex"
                      "clangParse"
                      "clangSema"
                      "clangEdit"
                      "clangSerialization"
                      "clangToolingCore"
                      "clangTooling"
                      "clangFormat")

# for debug
# message(STATUS "*** dump start cmake variables ***")
# get_cmake_property(_variableNames VARIABLES)
# foreach(_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
# message(STATUS "*** dump end ***")
