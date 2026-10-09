# AmiScene M2 native 68k reference build.
# The source is intentionally Motorola/vasm syntax; do not route it through GCC's assembler.
VASM ?= vasmm68k_mot
VLINK ?= vlink
VASMFLAGS ?= -m68000 -Fhunk -I../../include
VLINKFLAGS ?= -bamigahunk -Bstatic
OUT ?= build/amiscene-copper
QUALIFY_OUT ?= build/amiscene-copper-qualify
HUNK_RETURN_OUT ?= build/amiscene-hunk-return-smoke
BLIT_OUT ?= build/amiscene-blit-qualify
BLIT_FILL_OUT ?= build/amiscene-blit-fill-qualify
BLIT_LINE_OUT ?= build/amiscene-blit-line-qualify
BLIT_OCTANT0_SMOKE_OUT ?= build/amiscene-blit-line-octant0-smoke
BLIT_OCTANT0_ALLOC_SMOKE_OUT ?= build/amiscene-blit-line-octant0-alloc-smoke
BLIT_OCTANT0_ORACLE_SMOKE_OUT ?= build/amiscene-blit-line-octant0-oracle-smoke
BLIT_STAGE_OUT ?= build/amiscene-blit-line-stage-3
BLIT_STAGE2_OUT ?= build/amiscene-blit-line-stage2-3
BLIT_STAGE3_OUT ?= build/amiscene-blit-line-stage3-3
BLIT_STAGE4_OUT ?= build/amiscene-blit-line-stage4-3
BLIT_STAGE5_OUT ?= build/amiscene-blit-line-stage5-3
BLIT_OCTANTS_OUT ?= build/amiscene-blit-line-octants-qualify
BLIT_OCTANT_OUTS := $(foreach n,0 1 2 3 4 5 6 7,build/amiscene-blit-line-octant-$(n)-qualify)
BLIT_OCTANT3_ROWS := $(foreach n,1 2 3 4 5 6 7 8 9,build/amiscene-blit-line-octant-3-rows-$(n))
BLIT_PROBE_OFFSETS := m82 m80 m78 m42 m40 m38 m2 p2 p38 p40 p42 p78 p80 p82
BLIT_PROBE_OUTS := $(foreach n,$(BLIT_PROBE_OFFSETS),build/amiscene-blit-line-probe-$(n))

all: $(HUNK_RETURN_OUT) $(OUT) $(QUALIFY_OUT) $(BLIT_OUT) $(BLIT_FILL_OUT) $(BLIT_LINE_OUT) $(BLIT_OCTANT0_SMOKE_OUT) $(BLIT_OCTANT0_ALLOC_SMOKE_OUT) $(BLIT_OCTANT0_ORACLE_SMOKE_OUT) $(BLIT_STAGE_OUT) $(BLIT_STAGE2_OUT) $(BLIT_STAGE3_OUT) $(BLIT_STAGE4_OUT) $(BLIT_STAGE5_OUT) $(BLIT_OCTANTS_OUT) $(BLIT_OCTANT_OUTS) $(BLIT_OCTANT3_ROWS) $(BLIT_PROBE_OUTS)

build/hunk_return_smoke.o: hunk_return_smoke.s
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

$(HUNK_RETURN_OUT): build/hunk_return_smoke.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

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

build/blit_line_octant0_oracle_smoke.o: blit_line_octant0_oracle_smoke.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_probe_m%.o: blit_line_octant0_oracle_smoke.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DPROBE=-$* -o $@ $<

build/blit_line_probe_p%.o: blit_line_octant0_oracle_smoke.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DPROBE=$* -o $@ $<

build/blit_line_stage_3.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DSTAGE=1 -o $@ $<

$(BLIT_STAGE_OUT): build/blit_line_stage_3.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/blit_line_stage2_3.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DSTAGE=2 -o $@ $<

$(BLIT_STAGE2_OUT): build/blit_line_stage2_3.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/blit_line_stage3_3.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DSTAGE=3 -o $@ $<

$(BLIT_STAGE3_OUT): build/blit_line_stage3_3.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/blit_line_stage4_3.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DSTAGE=4 -o $@ $<

$(BLIT_STAGE4_OUT): build/blit_line_stage4_3.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/blit_line_stage5_3.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DSTAGE=5 -o $@ $<

$(BLIT_STAGE5_OUT): build/blit_line_stage5_3.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/blit_line_octants_qualify.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -o $@ $<

build/blit_line_octant_%-qualify.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=$* -o $@ $<

build/blit_line_octant3_rows_%.o: blit_line_octants_qualify.s ../../include/amiscene/ocs.i
	mkdir -p build
	$(VASM) $(VASMFLAGS) -DOCTANT=3 -DROW_LIMIT=$* -o $@ $<

build/amiscene-blit-line-octant-3-rows-%: build/blit_line_octant3_rows_%.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

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

$(BLIT_OCTANT0_ORACLE_SMOKE_OUT): build/blit_line_octant0_oracle_smoke.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/amiscene-blit-line-probe-m%: build/blit_line_probe_m%.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/amiscene-blit-line-probe-p%: build/blit_line_probe_p%.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

$(BLIT_OCTANTS_OUT): build/blit_line_octants_qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

build/amiscene-blit-line-octant-%-qualify: build/blit_line_octant_%-qualify.o build/blit_runtime.o
	$(VLINK) $(VLINKFLAGS) -o $@ $^

clean:
	rm -rf build

.PHONY: all clean
