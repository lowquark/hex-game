
include config.mk

build/%.o: %.c
	@mkdir --parents $(@D)
	clang $(CFLAGS) -c -o $@ $<

all: app test

app: $(APP_OBJS)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST_OBJS)
	clang $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -r build/
	rm app
	rm test

