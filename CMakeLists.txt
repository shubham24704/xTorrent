cmake_minimum_required(VERSION 3.13)

project(bittorrent)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Directory variables
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_DIR})

# Collect all source files
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.hpp)

# OpenSSL setup (macOS/Homebrew)
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
find_package(OpenSSL REQUIRED)

# ----------------------------
# Main BitTorrent executable
# ----------------------------
set(SOURCE_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/bencode.cpp
)
add_executable(bittorrent ${SOURCE_FILES})

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/lib)
target_include_directories(bittorrent PRIVATE
    ${SRC_DIR}
    ${LIB_DIR}
)

# Link OpenSSL (must come AFTER add_executable)
target_link_libraries(bittorrent PRIVATE OpenSSL::Crypto)

# ----------------------------
# Bencode test executable
# ----------------------------
add_executable(test_bencode
    ${TEST_DIR}/test_bencode.cpp
    ${SRC_DIR}/bencode.cpp
)

# ----------------------------
# Bencode test executable
# ----------------------------
add_executable(test_torrent_parser
    test/test_torrent_parser.cpp
    src/torrent_parser.cpp
    src/bencode.cpp
)

target_include_directories(test_bencode PRIVATE ${SRC_DIR} ${LIB_DIR})
target_link_libraries(test_bencode PRIVATE OpenSSL::Crypto)

# ----------------------------
# Custom target to run tests
# ----------------------------
add_custom_target(run_tests
    COMMAND test_bencode
    DEPENDS test_bencode
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "🧪 Running bencode tests..."
)
