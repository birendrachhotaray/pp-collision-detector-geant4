
# Setup the project
cmake_minimum_required(VERSION 3.16...3.27)

# My project name
project(G-space-suit)

# Find Geant4 with UI and visualisation support
find_package(Geant4 REQUIRED ui_all vis_all)

# Include all the Geant4 files
include(${Geant4_USE_FILE})

# Find PYTHIA installation
set(PYTHIA8_DIR "$ENV{PYTHIA8}")

if(NOT PYTHIA8_DIR)
    message(FATAL_ERROR "PYTHIA8 environment variable is not set")
endif()

find_library(PYTHIA8_LIBRARY
    NAMES pythia8
    PATHS "${PYTHIA8_DIR}/lib"
    NO_DEFAULT_PATH
)

if(NOT PYTHIA8_LIBRARY)
    message(FATAL_ERROR "PYTHIA8 library not found")
endif()

file(GLOB sources CONFIGURE_DEPENDS *.cc)
file(GLOB headers CONFIGURE_DEPENDS *.hh)

# Create executable
add_executable(G-space-suit
    ${sources}
    ${headers}
)

# Include PYTHIA headers
target_include_directories(G-space-suit PRIVATE
    "${PYTHIA8_DIR}/include"
)

# Link Geant4 and PYTHIA libraries
target_link_libraries(G-space-suit PRIVATE
    ${Geant4_LIBRARIES}
    ${PYTHIA8_LIBRARY}
)

# Find PYTHIA shared library at runtime
set_target_properties(G-space-suit PROPERTIES
    BUILD_RPATH "${PYTHIA8_DIR}/lib"
)
