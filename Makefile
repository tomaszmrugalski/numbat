tags:
	etags `find . -name '*.cc' -or -name '*.h' | xargs`

wimax:
	cd wimax; $(MAKE)


.PHONY: tags wimax
