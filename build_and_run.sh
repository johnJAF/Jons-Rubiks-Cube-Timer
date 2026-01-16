#!/bin/bash

echo "Starting build process..."


# Detect OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Detected macOS"
    COMPILER="g++"
    FLAGS="-std=c++17 -stdlib=libc++"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Detected Linux"
    COMPILER="g++"
    FLAGS="-std=c++17"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "win32" ]]; then
    echo "Detected Windows"
    COMPILER="g++"
    FLAGS="-std=c++17"
else
    echo "Unsupported OS: $OSTYPE"
    exit 1
fi

# Define output directory
OUTPUT_DIR="bin"
EXECUTABLE="$OUTPUT_DIR/main.exe"

# Define data directories
DATA_DIR="Data"
ALGORITHMS_DIR="$DATA_DIR/Algorithms"
OLL_DIR="$ALGORITHMS_DIR/OLL"
PLL_DIR="$ALGORITHMS_DIR/PLL"
SESSIONS_DIR="$DATA_DIR/Sessions"

# Create necessary directories
echo "Ensuring required directories exist..."
mkdir -p $OUTPUT_DIR
mkdir -p $OLL_DIR
mkdir -p $PLL_DIR
mkdir -p $SESSIONS_DIR

# Optional: create .gitkeep files for GitHub visibility
touch $DATA_DIR/.gitkeep
touch $ALGORITHMS_DIR/.gitkeep
touch $OLL_DIR/.gitkeep
touch $PLL_DIR/.gitkeep
touch $SESSIONS_DIR/.gitkeep


# Check if source files exist
if ! ls main\ code/*.cpp 1> /dev/null 2>&1; then
    echo "Error: No source files found in 'main code' directory."
    exit 1
fi

echo "Compiling..."
SRC_DIR="main code"
"$COMPILER" $FLAGS "$SRC_DIR"/*.cpp -o "$EXECUTABLE"

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program:"
    ./$EXECUTABLE
else
    echo "Compilation failed."
    exit 1
fi
