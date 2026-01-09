#!/bin/bash
# Auto-rebuild on file changes

set -e

BUILD_DIR="build"
TARGET="Klinker_Standalone"
CORES=$(nproc)

echo "👀 Watching Source/ for changes..."
echo "Press Ctrl+C to stop"
echo ""

# Build once at start
cmake --build "$BUILD_DIR" --target "$TARGET" -j"$CORES"

# Watch for changes (requires inotify-tools: dnf install inotify-tools)
while inotifywait -r -e modify,create,delete --exclude '\.(swp|swx)$' Source/; do
    echo ""
    echo "🔨 Change detected, rebuilding..."
    if cmake --build "$BUILD_DIR" --target "$TARGET" -j"$CORES"; then
        echo "✅ Build successful at $(date +%H:%M:%S)"
    else
        echo "❌ Build failed at $(date +%H:%M:%S)"
    fi
    echo ""
done
