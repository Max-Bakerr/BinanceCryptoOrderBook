cmake_minimum_required(VERSION 3.20)
project(orderbook LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17) #if a compiler supports C++17, use it, if not an error will be thrown (applies to line below as well)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

include(FetchContent) #loads the FetchContent module, which allows us to download and use external dependencies in our project

FetchContent_Declare(nlohmann_json   #declare a dependency called nlohman_json, which is the name of the library we want to use
    GIT_REPOSITORY https://github.com/nlohmann/json.git    
    GIT_TAG v3.12.0   #pinned tag to ensure we always use the same version of the library, which helps with reproducibility and stability
    GIT_SHALLOW TRUE)  #skips downloading the entire git history of the library, which saves time and disk space

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.0
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nlohmann_json Catch2)  #now that we have declared the dependency, we can make it available to our project, which allows us to use it in our code

#Shared code: compiled once, linked by both the program and the tests
add_library(ob_core src/pricing.cpp)
target_include_directories(ob_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src) 
#add the src directory to the include path for the ob_core library, which allows us to include header files from that directory in our code  

add_executable(ob src/main.cpp)
target_link_libraries(ob PRIVATE ob_core nlohmann_json::nlohmann_json)

enable_testing() #turns CTest on, which allows us to run tests using the CTest command
add_executable(ob_tests tests/test_pricing.cpp)
target_link_libraries(ob_tests PRIVATE ob_core Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(ob_tests) #adds a post-build step that runs binary with --list-tests, reads the names back and registers them with CTest, which allows us to run individual tests using the CTest command

#PRIVATE means ob need this to build but nothing that depends on ob needs it, PUBLIC means ob and anything that depends on ob needs it, INTERFACE means ob doesn't need it but anything that depends on ob does need it