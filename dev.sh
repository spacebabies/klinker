#!/bin/bash
# Fast development loop for Klinker

set -e

TARGET="Klinker_Standalone"
BUILD_DIR="build"
BINARY="$BUILD_DIR/${TARGET}_artefacts/Standalone/Klinker"

# Use all CPU cores for parallel builds
CORES=$(nproc)

echo "🔨 Building with $CORES cores..."
cmake --build "$BUILD_DIR" --target "$TARGET" -j"$CORES"

echo "✅ Build complete!"

# Auto-run if requested
if [[ "$1" == "--run" || "$1" == "-r" ]]; then
    echo "🎵 Starting Klinker..."
    "$BINARY"
fi
