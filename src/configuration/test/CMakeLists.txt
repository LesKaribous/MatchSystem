
# Set up testing
find_package(GTest REQUIRED) 

include_directories(${GTEST_INCLUDE_DIR})

# Add the test executable
add_executable(parser parser.cc)

# Link the test executable with Google Test and your library
target_link_libraries(parser PRIVATE Configuration ${GTEST_LIBRARIES})

# Register your test with CTest
enable_testing()
add_test(NAME parser COMMAND parser)
