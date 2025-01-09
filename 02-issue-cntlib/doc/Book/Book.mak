PWD_BOOKPDF := doc/Book

HTMLTOPDF := pandoc

TOPDFLAGS += -t typst

HTMLSRC += $(wildcard ./$(PWD_BOOKPDF)/*.html)

OUT_BOOK_NAME := book.pdf
OUT_BOOK := ./$(BUILD_DIR)/$(PWD_BOOKPDF)/$(OUT_BOOK_NAME)

mk_book: mkdir_bookpdf
	$(HTMLTOPDF) $(TOPDFLAGS) $(HTMLSRC) -o $(OUT_BOOK) || true

mkdir_bookpdf:
	@mkdir -p ./$(BUILD_DIR)/$(PWD_BOOKPDF) || true