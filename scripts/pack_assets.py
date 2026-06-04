#!/usr/bin/env python
import os
import struct
import sys
from PIL import Image

def bake_terrain(image_path, output_bin_path):
    print(f"[Asset Pipeline] Processing: {image_path}")

    if not os.path.exists(image_path):
        print(f"[Asset Pipeline] Error: Source image '{image_path}' not found")
        sys.exit(1)

    # Open image and force it to grayscale ('L' mode = 1 byte per pixel, 0-255)
    # If using 16-bit raw, you can adapt this to 'I;16' format
    img = Image.open(image_path).convert('L')
    width, height = img.size

    print(f"[Asset Pipeline] Log: Dimensions found '{width}x{height}' pixels")

    # Extract raw pixel bytes
    raw_pixels = img.tobytes()

    # Construct a custom engine header:
    # 'i' = 4-byte signed integer. We pack:
    #   [Magic Number, Width, Height]
    magic = 0x4345335F                  # "CE3_" in hex
    header = struct.pack('iii', magic, width, height)

    # Ensure output directory exists
    with open(output_bin_path, 'wb') as f:
        f.write(header)                 # 12 bytes of structural metadata
        f.write(raw_pixels)             # The actual continuous terrain grid bytes

    print(f"[Asset Pipeline] Success: Baked binary saved to -> {output_bin_path}")
    print(f"[Asset Pipeline]: Log: Total file size [{os.path.getsize(output_bin_path)} (bytes)]")


if __name__ == "__main__":
    SOURCE_IMG = "assets/heightmaps/heightmapper-idaho.png"
    OUTPUT_BIN = "assets/heightmaps/idaho.chunk"

    bake_terrain(SOURCE_IMG, OUTPUT_BIN)
