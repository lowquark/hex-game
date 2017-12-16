
include config.mk

all: game test

game: $(GAME_SRC)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST_SRC)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

