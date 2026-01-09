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

# Optional but recommended for faster builds
sudo dnf5 install ccache

# Optional for auto-rebuild on file changes
sudo dnf5 install inotify-tools
```

Debian/Ubuntu/Mint:

```bash
sudo apt update
sudo apt install build-essential cmake libasound2-dev libx11-dev libxext-dev libxinerama-dev libxrandr-dev libxcursor-dev libxcomposite-dev libfreetype6-dev libgl1-mesa-dev libcurl4-openssl-dev libwebkit2gtk-4.1-dev libgtk-3-dev

# Optional but recommended for faster builds
sudo apt install ccache

# Optional for auto-rebuild on file changes
sudo apt install inotify-tools
```

## Compile

```bash
git clone git@github.com:spacebabies/klinker.git
cd klinker
cmake -B build
cmake --build build --target Klinker_Standalone
```

## Development

For faster iteration during development, use the provided build scripts:

### Quick build and run
```bash
./dev.sh          # Build with all CPU cores
./dev.sh --run    # Build and immediately run the standalone app
```

### Auto-rebuild on file changes
```bash
./watch.sh        # Watches Source/ directory and rebuilds automatically
```

Run the standalone binary directly:
```bash
./build/Klinker_Standalone_artefacts/Standalone/Klinker
```

### Build optimizations
- **ccache**: Compiler cache dramatically speeds up rebuilds (automatically detected if installed)
- **Parallel builds**: Uses all available CPU cores via `-j$(nproc)`
- **Incremental builds**: ~2 seconds for single file changes

## License

This project is licensed under the GNU AGPLv3.
