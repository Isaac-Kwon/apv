

set(TEST_EXE
    ana0_read
)

# for now put the executables in the build root
# for compatibility with existing scripts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

foreach(exe ${TEST_EXE})
add_executable(${exe} ${exe}.cxx ${sources} ${headers})
set_property(TARGET ${exe} PROPERTY POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(${exe} APVA)
endforeach()

message(STATUS "Target Executable: ${TEST_EXE}")
