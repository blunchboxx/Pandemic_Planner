cmake_minimum_required(VERSION 3.29)
project(Pandemic_Planner)

set(CMAKE_CXX_STANDARD 17)

#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

# Find required packages for Crow
find_package(Threads REQUIRED)

# Find required packages for asio
find_package(asio CONFIG REQUIRED)

#pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(src)
include_directories(test-unit)
include_directories(${CROW_INCLUDE_DIR})
include_directories("/usr/local/Cellar/asio/1.30.2/include")

add_executable(Main
        src/main.cpp
        src/Hospital.cpp
        src/Hospital.h
        src/dataInput.cpp
        src/dataInput.h
)

# Link required libraries for Crow
target_link_libraries(Main PRIVATE Threads::Threads)
target_link_libraries(Main PRIVATE asio::asio)
target_link_libraries(Main PRIVATE -lws2_32 -lwsock32 )
if(MINGW)
    target_link_libraries(Main PRIVATE ws2_32)
endif()
# target_link_libraries(Main PRIVATE Boost::boost Boost::program_options)

add_executable(Tests
        test-unit/test.cpp
        src/Hospital.cpp
        src/Hospital.h
        src/dataInput.cpp
        src/dataInput.h
)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)