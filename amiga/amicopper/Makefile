CC ?= m68k-amigaos-gcc
CFLAGS ?= -m68000 -Os -Wall -Wextra -Iinclude
LDFLAGS ?=
SRC = src/main.c src/ui.c src/document.c src/copper.c src/parser.c src/file.c src/arexx_commands.c src/arexx_port.c
OUT = build/AmiCopper
all: $(OUT)
$(OUT): $(SRC) include/amicopper.h include/amicopper_ui.h include/amicopper_copper.h
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@
clean:
	rm -rf build
.PHONY: all clean
