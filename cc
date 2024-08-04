#!/bin/bash

# Check if enough arguments are provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <source_file> [output_file]"
    exit 1
fi

source_file="$1"
output_file="$2"

# Remove old generated directory if it exists
if [ -e "./generated" ]; then 
    rm -rf ./generated
fi
mkdir -p generated

# Compile with gcc
gcc -o ./generated/gcc "$source_file" -Oz -w #-static
if [ -e "./generated/gcc" ]; then
    size=$(stat -c%s "./generated/gcc")
    size_kb=$(echo "scale=2; $size / 1024" | bc)
    echo "gcc: compilation successful, output $size_kb kilobytes"
else
    echo "gcc: file failed to compile"
fi

# Compile with clang
clang -o ./generated/clang "$source_file" -Oz -w #-static
if [ -e "./generated/clang" ]; then
    size=$(stat -c%s "./generated/clang")
    size_kb=$(echo "scale=2; $size / 1024" | bc)
    echo "clang: compilation successful, output $size_kb kilobytes"
else
    echo "clang: file failed to compile"
fi

# Compile with tcc
tcc -o ./generated/tcc "$source_file" -w
if [ -e "./generated/tcc" ]; then
    size=$(stat -c%s "./generated/tcc")
    size_kb=$(echo "scale=2; $size / 1024" | bc)
    echo "tcc: compilation successful, output $size_kb kilobytes"
else
    echo "tcc: file failed to compile"
fi

# Determine output filename
if [ -z "$output_file" ]; then
    # If no output filename specified, use source filename minus extension
    base_name=$(basename "$source_file" .c)
    output_file="./${base_name}"
else
    # Use the specified output filename
    output_file="${output_file}"
fi

# Copy the tcc binary to the output file
if [ -e "./generated/tcc" ]; then
    cp ./generated/tcc "$output_file"
    echo "tcc binary copied to $output_file"
else
    echo "tcc binary not found, trying clang"
    if [ -e "./generated/clang" ]; then
      cp ./generated/clang "$output_file"
      echo "clang binary copied to $output_file"
    else 
      echo "clang binary not found"
    fi
fi
