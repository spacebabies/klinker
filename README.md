# Klinker

**Klinker** is an open-source musical delay and reverb plugin for vocals. It aims to combine lush atmospheric textures with a clean, rhythmic delay line.

Built with C++ and JUCE on Linux, aimed at cross-platform use (VST3).

## Features (Planned)
- Tape-style circular buffer delay.
- Algorithmic reverb integration.
- "Wisteria" visualizer (hanging delay lines).

## Building from Source (Linux/Fedora)

### Prerequisites

Fedora/RHEL:

```bash
sudo dnf5 install @c-development
sudo dnf5 install cmake alsa-lib-devel libX11-devel libXext-devel libXinerama-devel libXrandr-devel libXcursor-devel libXcomposite-devel freetype-devel libglvnd-devel libcurl-devel webkit2gtk4.1-devel gtk3-devel
```

Debian/Ubuntu/Mint:

```bash
sudo apt update
sudo apt install build-essential cmake libasound2-dev libx11-dev libxext-dev libxinerama-dev libxrandr-dev libxcursor-dev libxcomposite-dev libfreetype6-dev libgl1-mesa-dev libcurl4-openssl-dev libwebkit2gtk-4.1-dev libgtk-3-dev
```

## Compile

```bash
git clone [https://github.com/spacebabies/klinker.git](https://github.com/spacebabies/klinker.git)
cd klinker
cmake -B build
cmake --build build --target Klinker_Standalone
```

## License

This project is licensed under the GNU AGPLv3.