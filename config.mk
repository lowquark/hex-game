
# module sources
HEX_MODULE_SRC += src/hex/bresenham.c

GS_MODULE_SRC += src/gs/gs.c
GS_MODULE_SRC += src/gs/cellhash.c

GFX_MODULE_SRC += src/gfx/gfx.c

ASSET_MODULE_SRC += src/asset/png.c

GAME_MODULE_SRC += 

# module checks / test module
TEST_MODULE_SRC += src/test/test.c

TEST_MODULE_SRC += src/hex/check.c
TEST_MODULE_SRC += src/gs/check.c
TEST_MODULE_SRC += src/asset/check.c

# binaries
TEST_SRC += $(TEST_MODULE_SRC)
TEST_SRC += $(GS_MODULE_SRC)
TEST_SRC += $(HEX_MODULE_SRC)
TEST_SRC += src/test/main.c

GAME_SRC += $(HEX_MODULE_SRC)
GAME_SRC += $(GS_MODULE_SRC)
GAME_SRC += $(GFX_MODULE_SRC)
GAME_SRC += $(ASSET_MODULE_SRC)
GAME_SRC += $(GAME_MODULE_SRC)
GAME_SRC += $(TEST_MODULE_SRC)
GAME_SRC += src/game/main.c

CFLAGS += -Isrc/
CFLAGS += -g3
CFLAGS += -std=gnu99
CFLAGS += -Wpedantic
CFLAGS += -Wall
CFLAGS += -Wno-gnu-statement-expression

LIBS += -lSDL2
LIBS += -lm
LIBS += -lpng
LIBS += -lz
LIBS += -lcheck

