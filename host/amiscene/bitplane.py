"""Core indexed-pixel to Amiga planar conversion."""

def chunky_to_planar(pixels, width, height, planes):
    if width <= 0 or height <= 0 or width % 8:
        raise ValueError("width must be positive and divisible by 8")
    if planes < 1 or planes > 8:
        raise ValueError("planes must be 1..8")
    if len(pixels) != width * height:
        raise ValueError("pixel count does not match dimensions")
    limit=1 << planes
    if any(p < 0 or p >= limit for p in pixels):
        raise ValueError("pixel index exceeds plane depth")
    rowbytes=width//8
    out=[bytearray(rowbytes*height) for _ in range(planes)]
    for y in range(height):
        for x in range(width):
            value=pixels[y*width+x]
            mask=1 << (7-(x&7))
            pos=y*rowbytes+(x>>3)
            for plane in range(planes):
                if value & (1<<plane):
                    out[plane][pos] |= mask
    return [bytes(p) for p in out]

def interleave(planes):
    if not planes: return b""
    size=len(planes[0])
    if any(len(p)!=size for p in planes): raise ValueError("plane sizes differ")
    return b"".join(p[i:i+1] for i in range(size) for p in planes)
