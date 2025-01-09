PWD_EXHELLO := examples/HelloWorld

SOURCES_EXHELLO += $(SOURCES)
SOURCES_EXHELLO += $(wildcard $(PWD_EXHELLO)/*.c)

OUT_HELLO_NAME := HelloWorld.out
OUT_HELLO := ./$(BUILD_DIR)/$(PWD_EXHELLO)/$(OUT_HELLO_NAME)

mk_exhello: mkdir_exhello
	$(CC) $(INCLUDES) $(SOURCES_EXHELLO) $(CFLAGS) -o $(OUT_HELLO)

mkdir_exhello:
	@mkdir -p ./$(BUILD_DIR)/$(PWD_EXHELLO)