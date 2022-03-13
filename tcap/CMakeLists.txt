# Copyright © 2022 The Certsar Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#   ██████╗███████╗██████╗ ████████╗███████╗ █████╗ ██████╗
#  ██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██╔══██╗
#  ██║     █████╗  ██████╔╝   ██║   ███████╗███████║██████╔╝
#  ██║     ██╔══╝  ██╔══██╗   ██║   ╚════██║██╔══██║██╔══██╗
#  ╚██████╗███████╗██║  ██║   ██║   ███████║██║  ██║██║  ██║
#   ╚═════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝
#
#
######################################################################
set(TCAP_SO_VERSION "0.0.1")  # Note: Update /src/version.h as well! #
######################################################################

cmake_minimum_required(VERSION 3.9)
project(tcap VERSION ${TCAP_SO_VERSION} DESCRIPTION "TLS Capture Library")

#
# Define all internal files
#
add_library(tcap SHARED
        src/tcap.c
        )

find_package(OpenSSL REQUIRED)
target_link_libraries(tcap OpenSSL::SSL)

#
# Version of the library properties
#
set_target_properties(tcap PROPERTIES VERSION ${TCAP_SO_VERSION})
#
# This is where the magic symlinking in /usr/include comes to play
set_target_properties(tcap PROPERTIES SOVERSION ${TCAP_SO_VERSION})

#
# Everything in /include will be what we expose as API
#
set_target_properties(tcap PROPERTIES PUBLIC_HEADER include/tcap.h)

# Add the top level directory to make our #include statements cleaner
target_include_directories(tcap PRIVATE .)
# Add include (public API)
target_include_directories(tcap PRIVATE include)
# Add src (private implementation)
target_include_directories(tcap PRIVATE src)

# make install
# Here is the install rule
include(GNUInstallDirs)
# This is where we put the shared object on the filesystem
install(TARGETS tcap
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})