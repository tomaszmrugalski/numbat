DIR=`basename $(PWD)`

tags:
	etags `find . -name '*.cc' -or -name '*.h' | xargs`

wimax:
	cd wimax; $(MAKE)

snapshot: clean
	rm -f numbat-*-svn.tar.gz
	cd ..; tar czvf numbat-svn.tar.gz --exclude=.svn --exclude=*~ $(DIR)
	mv ../numbat-svn.tar.gz numbat-`date +%Y%m%d`-svn.tar.gz

clean:
	cd wimax; $(MAKE) clean

.PHONY: tags wimax clean
