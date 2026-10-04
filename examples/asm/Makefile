# AmiScene M2 native 68k reference build.
# The source is intentionally Motorola/vasm syntax; do not route it through GCC's assembler.
VASM ?= vasmm68k_mot
VLINK ?= vlink
VASMFLAGS ?= -m68000 -Fhunk -I../../include
VLINKFLAGS ?= -bamigahunk -Bstatic
OUT ?= build/amiscene-copper
QUALIFY_OUT ?= build/amiscene-copper-qualify
BLIT_OUT ?= build/amiscene-blit-qualify
BLIT_FILL_OUT ?= build/amiscene-blit-fill-qualify
BLIT_LINE_OUT ?= build/amiscene-blit-line-qualify
BLIT_OCTANT0_SMOKE_OUT ?= build/amiscene-blit-line-octant0-smoke
BLIT_OCTANT0_ALLOC_SMOKE_OUT ?= build/amiscene-blit-line-octant0-alloc-smoke
BLIT_OCTANTS_OUT ?= build/amiscene-blit-line-octants-qualify
BLIT_OCTANT_OUTS := $(foreach n,0 1 2 3 4 5 6 7,build/amiscene-blit-line-octant-$(n)-qualify)

all: $(OUT) $(QUALIFY_OUT) $(BLIT_OUT) $(BLIT_FILL_OUT) $(BLIT_LINE_OUT) $(BLIT_OCTANT0_SMOKE_OUT) $(BLIT_OCTANT0_ALLOC_SMOKE_OUT) $(BLIT_OCTANTS_OUT) $(BLIT_OCTANT_OUTS)

build/copper_minimal.o: copper_minimal.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/copper_qualify.o: copper_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_qualify.o: blit_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_fill_qualify.o: blit_fill_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_qualify.o: blit_line_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_octant0_smoke.o: blit_line_octant0_smoke.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_octant0_alloc_smoke.o: blit_line_octant0_alloc_smoke.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_octants_qualify.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_octant_%-qualify.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=$* -o $@ $<

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

$(BLIT_FILL_OUT): build/blit_fill_qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_LINE_OUT): build/blit_line_qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_OCTANT0_SMOKE_OUT): build/blit_line_octant0_smoke.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_OCTANT0_ALLOC_SMOKE_OUT): build/blit_line_octant0_alloc_smoke.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_OCTANTS_OUT): build/blit_line_octants_qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/amiscene-blit-line-octant-%-qualify: build/blit_line_octant_%-qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

clean:
	rm -rf build

.PHONY: all clean
