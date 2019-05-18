INSTALL = install
DESTDIR = /usr/local/bin
ARFLAGS = rcs
APP_DIR = app
TEST_DIR = test
APP_FILE = $(APP_DIR)/poet
TEST_FILE = $(TEST_DIR)/poettest
TEST_SRC = $(TEST_DIR)/poettest.c
APP_OBJS = $(APP_DIR)/poet.o $(APP_DIR)/getoptions.o
APP_SRC = $(APP_DIR)/poet.c $(APP_DIR)/getoptions.c
LIB_DIR = lib
LIB_FILE = $(LIB_DIR)/libpoet.la
LIB_OBJS = $(LIB_DIR)/poet.o
OBJS = $(APP_OBJS) $(LIB_OBJS)
INCLUDES = -I. -I./lib
CFLAGS = $(INCLUDES) -DHAVE_CONFIG_H `pkg-config --cflags glib-2.0`

.PHONY: all
all: $(APP_FILE) $(TEST_FILE)

$(APP_FILE): $(APP_SRC) $(LIB_FILE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ `pkg-config --libs glib-2.0`

$(TEST_FILE): $(TEST_SRC) $(LIB_FILE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ `pkg-config --libs glib-2.0`

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

.PHONY: test
test: $(TEST_FILE)
	$(TEST_FILE)

.PHONY: install
install: $(APP_FILE)
	$(INSTALL) $(APP_FILE) $(DESTDIR)

.PHONY: clean
clean:
	$(RM) $(APP_FILE) $(LIB_FILE) $(OBJS)

EXTRA_DIST = Doxyfile exampledata/*.txt doc/overview.html apidoc

.PHONY: apidoc
apidoc:
	doxygen

# This removes the doc dir, so it doesnt clutter up CVS with its files
# when committing. ??? How can i arrange for this to be called from
# make maintainer-clean?
docclean:
	rm -fr apidoc
