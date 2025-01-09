CC = gcc

INCLUDES += -I"."

SOURCES += cntlib/*.c

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -g
CFLAGS += -O0

BUILD_DIR := build

EXAMPLE_LIST += mk_exhello
EXAMPLE_LIST += mk_extzone
EXAMPLE_LIST += mk_book

all: mk_info $(EXAMPLE_LIST)

include doc/Book/Book.mak
include examples/HelloWorld/HelloWorld.mak
include examples/TimeZone/TimeZone.mak

mk_info:
	@echo "The following packages are required for successful compilation:"
	@echo "gcc, pandoc, texlive, typst"
	@echo ""
	@echo "MIT license"
	@echo "Copyright (c) 2024-2025 Orcali"
	@echo "=============================="

clean:
	rm -rf $(BUILD_DIR)