cmake_minimum_required(VERSION 3.13)

project(codecrafters-bittorrent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
find_package(OpenSSL REQUIRED)

add_executable(bittorrent ${SOURCE_FILES})

# Add include directories for headers in src/ and lib/
target_include_directories(bittorrent PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

# Link OpenSSL
target_link_libraries(bittorrent PRIVATE OpenSSL::Crypto)
