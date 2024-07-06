EXTRA_DIST = Doxyfile exampledata/*.txt doc/overview.html apidoc

SUBDIRS = lib app test

.PHONY: apidoc
apidoc:
	doxygen

# This removes the doc dir, so it doesnt clutter up CVS with its files
# when committing. ??? How can i arrange for this to be called from
# make maintainer-clean?
docclean:
	rm -fr apidoc

# This may not be the most elegant way to call Valgrind, but for starters ...
.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --track-origins=yes test/.libs/poettest

.PHONY: vagrant
vagrant:
	- vagrant destroy -f
	vagrant up
