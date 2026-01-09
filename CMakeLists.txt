cmake_minimum_required(VERSION 3.22)

project(Klinker VERSION 0.0.1)

# 1. JUCE is a hard dependency
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.12
)
FetchContent_MakeAvailable(juce)

# 2. Define the Plugin
juce_add_plugin(Klinker
    COMPANY_NAME "Space Babies"
    BUNDLE_ID "nl.spacebabies.Klinker"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    # Formats to build
    FORMATS VST3 Standalone
    # 4-alpha unique code
    PLUGIN_CODE SBKl
    PRODUCT_NAME "Klinker"
)

# 3. My source
target_sources(Klinker
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
)

# 4. Link against JUCE libraries
target_link_libraries(Klinker
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# ==============================================================================
# 5. LINUX SYSTEM DEPENDENCIES FIX
# ==============================================================================
if((CMAKE_SYSTEM_NAME STREQUAL "Linux") OR (CMAKE_SYSTEM_NAME MATCHES ".*BSD"))
    find_package(PkgConfig REQUIRED)

    # GTK3 (GUI)
    pkg_check_modules(GTK3 REQUIRED gtk+-x11-3.0)

    # WebKit (Browser component)
    pkg_check_modules(WEBKIT webkit2gtk-4.1)

    # cURL (Networking - Required by juce_core on Linux)
    pkg_check_modules(CURL REQUIRED libcurl)

    # Add the include paths
    target_include_directories(Klinker PRIVATE
        ${GTK3_INCLUDE_DIRS}
        ${WEBKIT_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIRS}
    )

    # Link the system libraries
    target_link_libraries(Klinker PRIVATE
        ${GTK3_LIBRARIES}
        ${WEBKIT_LIBRARIES}
        ${CURL_LIBRARIES}
    )
endif()