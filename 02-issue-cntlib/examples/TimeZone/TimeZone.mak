PWD_EXTZONE := examples/TimeZone

SOURCES_EXTZONE += $(SOURCES)
SOURCES_EXTZONE += $(wildcard $(PWD_EXTZONE)/*.c)

OUT_TZONE_NAME := TimeZone.out
OUT_TZONE := ./$(BUILD_DIR)/$(PWD_EXTZONE)/$(OUT_TZONE_NAME)

mk_extzone: mkdir_extzone
	$(CC) $(INCLUDES) $(SOURCES_EXTZONE) $(CFLAGS) -o $(OUT_TZONE)

mkdir_extzone:
	@mkdir -p ./$(BUILD_DIR)/$(PWD_EXTZONE)