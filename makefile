
include config.mk

%.o: %.c
	clang $(CFLAGS) -c -o $@ $<

all: app test

app: $(APP_OBJS)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST_OBJS)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

