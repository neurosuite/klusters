# SPDX-License-Identifier: GPL-3.0-or-later
cmake_minimum_required(VERSION 3.16)
project(klusters
    VERSION 3.0.0
    DESCRIPTION "Cluster cutting application for spike sorting"
    HOMEPAGE_URL "https://neurosuite.github.io"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(KLUSTERS_BUNDLE_NEUROSUITE
       "Build libneurosuite as part of this project instead of using an installed copy"
       OFF)
set(NEUROSUITE_GIT_TAG "v3.0.0" CACHE STRING
    "libneurosuite tag to fetch when KLUSTERS_BUNDLE_NEUROSUITE is ON")

if(APPLE)
    option(APPBUNDLE "Produce a macOS .app bundle" OFF)
endif()

include(GNUInstallDirs)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find a bundled libneurosuite next to the binary (AppImage, macOS bundle, relocatable installs)
if(APPBUNDLE)
    set(NEUROSUITE_BUNDLED_LIBDIR "klusters.app/Contents/Frameworks")
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
elseif(APPLE)
    set(CMAKE_INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()

# Ship the MSVC runtime next to the executable on Windows.
if(WIN32)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR})
    include(InstallRequiredSystemLibraries)
endif()

if(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-Dfseeko64=_fseeki64)
    add_definitions(-Dftello64=_ftelli64)
endif()

if(APPLE)
    # File operations are always 64 bit on macOS.
    add_definitions(-Dfseeko64=fseeko)
    add_definitions(-Dftello64=ftello)
endif()

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_USE_QSTRINGBUILDER)
find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets PrintSupport Xml)

if(KLUSTERS_BUNDLE_NEUROSUITE)
    include(FetchContent)
    FetchContent_Declare(neurosuite
        GIT_REPOSITORY https://github.com/neurosuite/libneurosuite.git
        GIT_TAG ${NEUROSUITE_GIT_TAG}
    )
    FetchContent_MakeAvailable(neurosuite)
else()
    find_package(neurosuite 3.0 REQUIRED)
endif()

if(APPBUNDLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME "Klusters")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.neurosuite.Klusters")
endif()

# The handbook is looked up relative to the executable at runtime.
if(APPBUNDLE)
    set(KLUSTERS_DOC_INSTALL_DIR "klusters.app/Contents/Documentation")
    set(KLUSTERS_DOC_RELATIVE_PATH "../Documentation")
else()
    set(KLUSTERS_DOC_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/doc/klusters/HTML/en")
    file(RELATIVE_PATH KLUSTERS_DOC_RELATIVE_PATH
         "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
         "${CMAKE_INSTALL_PREFIX}/${KLUSTERS_DOC_INSTALL_DIR}")
endif()

configure_file(config-klusters.h.cmake src/config-klusters.h)

add_subdirectory(src)
add_subdirectory(doc)

include(cmake/CPackConfig.cmake)
