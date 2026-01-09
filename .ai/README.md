# Klinker AI Context & Development Notes

## Project Overview
- **Name:** Klinker
- **Type:** Audio Plugin (VST3, Standalone)
- **Framework:** JUCE 8 (via CMake FetchContent)
- **Language:** C++ (C++20 standard)
- **License:** AGPLv3
- **Target OS:** Linux (Fedora KDE / Wayland), cross-platform compatible code.

## Code Style & Conventions
- **Comments:** ALWAYS in English.
- **Code:** ALWAYS in English.
- **Class Names:** English (avoid Dutch naming in code).
- **Format:** K&R or Allman, keep it consistent.
- **Modern C++:** Use `auto`, `nullptr`, smart pointers where possible.
- Prefer JUCE internal modules over external libs unless necessary (e.g. strict real-time safety).

## Build System (CMake)
- **Do NOT use Projucer.** We use a native CMake workflow.
- **Source:** `Source/PluginProcessor.h/cpp` (Logic) & `Source/PluginEditor.h/cpp` (GUI).
- **Build Command:** `cmake -B build && cmake --build build --target Klinker_Standalone`
- **Known Linux Issues (Fixed in CMakeLists.txt):**
  - Explicitly links `gtk+-x11-3.0` and `webkit2gtk-4.1` headers via PkgConfig.
  - Explicitly links `libcurl` (required by `juce_core`).
  - `JuceHeader.h` is NOT available. Include specific modules (e.g., `#include <juce_audio_utils/juce_audio_utils.h>`).

## Current Status
- Basic "Hello World" builds and runs.
- Bundle ID set to `nl.spacebabies.Klinker`.
- Delay engine (circular buffer) logic is drafted but NOT yet implemented in main branch.