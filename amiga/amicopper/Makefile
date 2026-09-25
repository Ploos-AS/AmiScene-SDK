AMIGA_CC ?= m68k-amigaos-gcc
HOST_CC ?= cc
CFLAGS ?= -m68000 -Os -Wall -Wextra -Iinclude
LDFLAGS ?=
SRC = src/main.c src/ui.c src/document.c src/copper.c src/parser.c src/file.c src/arexx_commands.c src/arexx_port.c
OUT = build/AmiCopper
TEST = build/test-roundtrip
all: $(OUT)
$(OUT): $(SRC) include/amicopper.h include/amicopper_ui.h include/amicopper_copper.h
	mkdir -p build
	$(AMIGA_CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@
test: $(TEST)
	$(TEST)
$(TEST): tests/test_roundtrip.c src/parser.c src/copper.c include/amicopper.h include/amicopper_copper.h
	mkdir -p build
	$(HOST_CC) -std=c99 -Wall -Wextra -Iinclude tests/test_roundtrip.c src/parser.c src/copper.c -o $@
clean:
	rm -rf build
.PHONY: all test clean
