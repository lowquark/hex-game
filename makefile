
include config.mk

all: app test

app: $(APP_SRC)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST_SRC)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

