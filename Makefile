ARFLAGS = rcs
APP_DIR = app
APP_FILE = $(APP_DIR)/poet
APP_OBJS = $(APP_DIR)/poet.o $(APP_DIR)/getoptions.o
APP_SRC = $(APP_DIR)/poet.c $(APP_DIR)/getoptions.c
LIB_DIR = lib
LIB_FILE = $(LIB_DIR)/libpoet.la
LIB_OBJS = $(LIB_DIR)/poet.o
OBJS = $(APP_OBJS) $(LIB_OBJS)
INCLUDES = -I. -I./lib
CFLAGS = $(INCLUDES) -DHAVE_CONFIG_H `pkg-config --cflags glib-2.0`
BASE_LIB = -lNikBaseC

.PHONY: all
all: $(APP_FILE)

$(APP_FILE): $(APP_SRC) $(LIB_FILE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ `pkg-config --libs glib-2.0` $(BASE_LIB)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

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
