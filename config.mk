
# module sources
HEX_MODULE_SRC += src/hex/bresenham.c

GFX_MODULE_SRC += src/gfx/gfx.c

SCENE_MODULE_SRC += src/scene/scene.c
SCENE_MODULE_SRC += src/scene/draw.c
SCENE_MODULE_SRC += src/scene/tiles.c
SCENE_MODULE_SRC += src/scene/objects.c
SCENE_MODULE_SRC += src/scene/object.c
SCENE_MODULE_SRC += src/scene/sprites.c

ASSET_MODULE_SRC += src/asset/png.c
ASSET_MODULE_SRC += src/asset/lodepng.c

GAME_MODULE_SRC += src/game/game.c

UTIL_MODULE_SRC += src/util/hash_2i.c
UTIL_MODULE_SRC += src/util/hash_ul.c

# module checks / test module
TEST_MODULE_SRC += src/test/test.c

TEST_MODULE_SRC += src/hex/check.c
TEST_MODULE_SRC += src/asset/check.c
TEST_MODULE_SRC += src/util/check.c

# binaries
TEST_SRC += $(TEST_MODULE_SRC)
TEST_SRC += $(HEX_MODULE_SRC)
TEST_SRC += $(UTIL_MODULE_SRC)
TEST_SRC += src/test/main.c

APP_SRC += $(HEX_MODULE_SRC)
APP_SRC += $(UTIL_MODULE_SRC)
APP_SRC += $(GFX_MODULE_SRC)
APP_SRC += $(SCENE_MODULE_SRC)
APP_SRC += $(ASSET_MODULE_SRC)
APP_SRC += $(GAME_MODULE_SRC)
APP_SRC += $(TEST_MODULE_SRC)
APP_SRC += src/app/main.c

CFLAGS += -Isrc/
CFLAGS += -g3
CFLAGS += -std=c99

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpedantic

CFLAGS += -Wno-unused-parameter
CFLAGS += -Werror=implicit-function-declaration
CFLAGS += -Werror=int-conversion
CFLAGS += -Werror=strict-prototypes

LIBS += -lSDL2
LIBS += -lm
LIBS += -lcheck

