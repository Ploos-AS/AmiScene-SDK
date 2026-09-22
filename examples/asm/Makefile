# M2 native 68k reference build
# Uses the Bebbo/m68k-amigaos toolchain convention used by Ploos-AS amiga-dev.
CC ?= m68k-amigaos-gcc
CFLAGS ?= -m68000 -Os -nostdlib -nostartfiles
ASFLAGS ?= -Wa,-I../../include
OUT ?= build/amiscene-copper

all: $(OUT)

$(OUT): copper_minimal.s ../../runtime/asm/ocs/copper.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(CC) $(CFLAGS) $(ASFLAGS) -o $@ copper_minimal.s ../../runtime/asm/ocs/copper.s

clean:
	rm -rf build

.PHONY: all clean
