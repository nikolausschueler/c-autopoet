EXTRA_DIST = Doxyfile

SUBDIRS = lib app doc

dist-hook:
	echo "DISTHOOK WAS CALLED"

install-hook:
	echo "INSTALLHOOK WAS CALLED"

apidoc:
	doxygen

# This removes the doc dir, so it doesnt clutter up CVS with its files
# when committing. ??? How can i arrange for this to be called from
# make maintainer-clean?
docclean:
	rm -fr apidoc
