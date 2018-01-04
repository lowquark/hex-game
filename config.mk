
# module sources
HEX_MODULE_SRC += hex/bresenham

GFX_MODULE_SRC += gfx/gfx

SCENE_MODULE_SRC += scene/scene
SCENE_MODULE_SRC += scene/view
SCENE_MODULE_SRC += scene/tile
SCENE_MODULE_SRC += scene/object
SCENE_MODULE_SRC += scene/tiles
SCENE_MODULE_SRC += scene/objects
SCENE_MODULE_SRC += scene/sprites

ASSET_MODULE_SRC += asset/png
ASSET_MODULE_SRC += asset/lodepng

GAME_MODULE_SRC += game/game
GAME_MODULE_SRC += game/handlers

UTIL_MODULE_SRC += util/hash_2i
UTIL_MODULE_SRC += util/hash_ul
UTIL_MODULE_SRC += util/list

# module checks / test module
TEST_MODULE_SRC += test/test

TEST_MODULE_SRC += hex/check
TEST_MODULE_SRC += asset/check
TEST_MODULE_SRC += util/check

# binaries
TEST_SRC += $(TEST_MODULE_SRC)
TEST_SRC += $(HEX_MODULE_SRC)
TEST_SRC += $(UTIL_MODULE_SRC)
TEST_SRC += test/main

APP_SRC += $(HEX_MODULE_SRC)
APP_SRC += $(UTIL_MODULE_SRC)
APP_SRC += $(GFX_MODULE_SRC)
APP_SRC += $(SCENE_MODULE_SRC)
APP_SRC += $(ASSET_MODULE_SRC)
APP_SRC += $(GAME_MODULE_SRC)
APP_SRC += $(TEST_MODULE_SRC)
APP_SRC += app/main

APP_SRC := $(addprefix src/,$(APP_SRC))
TEST_SRC := $(addprefix src/,$(TEST_SRC))

TEST_OBJS = $(patsubst %,build/%.o,$(TEST_SRC))
APP_OBJS = $(patsubst %,build/%.o,$(APP_SRC))

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

