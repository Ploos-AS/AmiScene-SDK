# AmiScene M2 native 68k reference build.
# The source is intentionally Motorola/vasm syntax; do not route it through GCC's assembler.
VASM ?= vasmm68k_mot
VLINK ?= vlink
VASMFLAGS ?= -m68000 -Fhunk -I../../include
VLINKFLAGS ?= -bamigahunk -Bstatic
OUT ?= build/amiscene-copper
QUALIFY_OUT ?= build/amiscene-copper-qualify
BLIT_OUT ?= build/amiscene-blit-qualify

all: $(OUT) $(QUALIFY_OUT) $(BLIT_OUT)

build/copper_minimal.o: copper_minimal.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/copper_qualify.o: copper_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_qualify.o: blit_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_runtime.o: ../../runtime/asm/ocs/blit.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/copper_runtime.o: ../../runtime/asm/ocs/copper.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

$(OUT): build/copper_minimal.o build/copper_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(QUALIFY_OUT): build/copper_qualify.o build/copper_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_OUT): build/blit_qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

clean:
	rm -rf build

.PHONY: all clean
