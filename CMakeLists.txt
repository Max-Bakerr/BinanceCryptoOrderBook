cmake_minimum_required(VERSION 3.20)
project(orderbook LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17) #if a compiler supports C++17, use it, if not an error will be thrown (applies to line below as well)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

include(FetchContent) #loads the FetchContent module, which allows us to download and use external dependencies in our project

FetchContent_Declare(nlohmann_json   #declare a dependency called nlohman_json, which is the name of the library we want to use
    GIT_REPOSITORY https://github.com/nlohmann/json.git    
    GIT_TAG v3.12.0   #pinned tag to ensure we always use the same version of the library, which helps with reproducibility and stability
    GIT_SHALLOW TRUE)  #skips downloading the entire git history of the library, which saves time and disk space

FetchContent_MakeAvailable(nlohmann_json)  #now that we have declared the dependency, we can make it available to our project, which allows us to use it in our code

add_executable(ob src/main.cpp src/pricing.cpp) #create an executable called ob from the source files listed, which will be built when we run cmake
target_link_libraries(ob PRIVATE nlohmann_json::nlohmann_json)  #link the nlohmann_json library to our executable, which allows us to use its functionality in our code

#PRIVATE means ob need this to build but nothing that depends on ob needs it, PUBLIC means ob and anything that depends on ob needs it, INTERFACE means ob doesn't need it but anything that depends on ob does need it