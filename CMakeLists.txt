cmake_minimum_required (VERSION 3.16)

# Back compatibility for VERSION range
if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy (VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

project (BitcoinCalc CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Boost 1.86 COMPONENTS thread chrono log_setup log REQUIRED)
# if we do not have boost
#   * linux:
#     * go to the boost website, download and extract the latest version.
#     * `./bootstrap.sh`
#     * `./b2`
#     * `sudo ./b2 install`

add_definitions ("-DHAS_BOOST")

find_package (OpenSSL REQUIRED Crypto SSL)
# if we do not have openssl
#   * on linux, `sudo apt-get install libssl-dev`

find_package (SECP256K1 REQUIRED)
# if we do not have SECP256K1
#   * on linux
#     * go to `https://github.com/bitcoin-core/secp256k1`, download the repo, and follow the instructions.
#     * you mighht need autoconf: `sudo apt install autoconf`
#     * and libtool: `sudo apt-get install libtool-bin`

find_package (pegtl REQUIRED)
# If we do not have PegTL
#   * on linux, `sudo apt-get install tao-pegtl-dev`

find_package (PkgConfig REQUIRED)

IF (WIN32)
  pkg_check_modules (cryptopp REQUIRED IMPORTED_TARGET cryptopp)
ELSE ()
  pkg_check_modules (cryptopp REQUIRED IMPORTED_TARGET libcrypto++)
  # If we do not have crypto++, go to `https://github.com/weidai11/cryptopp` and follow the instructions.
ENDIF ()

include (FetchContent)
FetchContent_Declare (json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable (json)

FetchContent_Declare (argh URL https://github.com/adishavit/argh/archive/refs/tags/v1.3.2.zip)
FetchContent_MakeAvailable (argh)

FetchContent_Declare (ctre URL https://github.com/hanickadot/compile-time-regular-expressions/archive/refs/tags/v3.9.0.zip)
FetchContent_MakeAvailable (ctre)

find_package (data CONFIG REQUIRED)

find_package (gigamonkey CONFIG REQUIRED)

add_library (calc
    source/initialize.cpp
    source/machine.cpp
    source/replace.cpp
    source/parse.cpp
    source/expression.cpp
    source/nodes.cpp
    source/type.cpp
    source/pattern.cpp
    source/built.in/scriptnum.cpp
    source/built.in/modular.cpp
    source/built.in/pubkey.cpp
    source/built.in/string.cpp
    source/built.in/base58.cpp
    source/built.in/hash.cpp
    source/values/list.cpp
)

target_link_libraries (calc PUBLIC nlohmann_json argh Gigamonkey::gigamonkey Data::data)
target_include_directories (calc PUBLIC include)

target_compile_features (calc PUBLIC cxx_std_20)
set_target_properties (calc PROPERTIES CXX_EXTENSIONS OFF)

add_executable (BitcoinCalc calculator.cpp)

target_link_libraries (BitcoinCalc PUBLIC nlohmann_json argh calc Gigamonkey::gigamonkey Data::data)
target_include_directories (BitcoinCalc PUBLIC include)

target_compile_features (BitcoinCalc PUBLIC cxx_std_20)
set_target_properties (BitcoinCalc PROPERTIES CXX_EXTENSIONS OFF)

install (DIRECTORY include/ DESTINATION include)
install (TARGETS BitcoinCalc)

# Check if GTests is installed. If not, install it
option (PACKAGE_TESTS "Build the tests" ON)
include (CTest)

if (PACKAGE_TESTS)
  include (CTest)
  FetchContent_Declare (
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )

  set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable (googletest)
  enable_testing ()
  add_subdirectory (test)
endif ()

