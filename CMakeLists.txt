cmake_minimum_required (VERSION 3.16)

# Back compatibility for VERSION range
if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy (VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

project (
  BitcoinCalc
  VERSION 0.0.2
  LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 23)
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

add_library (
    diophant
    source/Diophant/initialize.cpp
    source/Diophant/machine.cpp
    source/Diophant/replace.cpp
    source/Diophant/parse.cpp
    source/Diophant/expression.cpp
    source/Diophant/nodes.cpp
    source/Diophant/type.cpp
    source/Diophant/pattern.cpp
    source/Diophant/values/list.cpp
    source/Diophant/values/struct.cpp
    source/Diophant/built.in/bool.cpp
    source/Diophant/built.in/numbers.cpp
    source/Diophant/built.in/scriptnum.cpp
    source/Diophant/built.in/modular.cpp
    source/Diophant/built.in/pubkey.cpp
    source/Diophant/built.in/string.cpp
    source/Diophant/built.in/base58.cpp
    source/Diophant/built.in/hash.cpp
    source/Diophant/built.in/hd.cpp
)

target_link_libraries (diophant PUBLIC nlohmann_json argh Gigamonkey::gigamonkey Data::data)

target_include_directories (diophant
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features (diophant PUBLIC cxx_std_20)
set_target_properties (diophant PROPERTIES CXX_EXTENSIONS OFF)

add_executable (BitcoinCalc calculator.cpp)

target_link_libraries (BitcoinCalc PUBLIC nlohmann_json argh diophant Gigamonkey::gigamonkey Data::data)
target_include_directories (BitcoinCalc PUBLIC include)

target_compile_features (BitcoinCalc PUBLIC cxx_std_20)
set_target_properties (BitcoinCalc PROPERTIES CXX_EXTENSIONS OFF)

# copy include directory into install destination
install (
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (
  TARGETS diophant nlohmann_json argh
  EXPORT diophantTargets
  ARCHIVE
)

install (
  EXPORT diophantTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/diophant
  FILE diophantTargets.cmake
  NAMESPACE diophant::
)

include (CMakePackageConfigHelpers)

# generate the config file that includes the exports
configure_package_config_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/diophantConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/diophant"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file (
  "${CMAKE_CURRENT_BINARY_DIR}/diophantConfigVersion.cmake"
  COMPATIBILITY AnyNewerVersion
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/diophantConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/diophantConfigVersion.cmake
  DESTINATION lib/cmake/diophant
)

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

# Default to Debug if no build type is specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set (CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif ()

# Optional: Show message
message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
