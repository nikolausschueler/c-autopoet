EXTRA_DIST = Doxyfile exampledata/*.txt doc/overview.html apidoc

SUBDIRS = lib app

apidoc:
	doxygen

# This removes the doc dir, so it doesnt clutter up CVS with its files
# when committing. ??? How can i arrange for this to be called from
# make maintainer-clean?
docclean:
	rm -fr apidoc
