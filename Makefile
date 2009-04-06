DIR=`basename $(PWD)`

all: util ipv6 wimax

tags:
	etags `find . -name '*.cc' -or -name '*.h' | xargs`

snapshot: clean
	rm -f numbat-*-svn.tar.gz
	cd ..; tar czvf numbat-svn.tar.gz --exclude=.svn --exclude=*~ $(DIR)
	mv ../numbat-svn.tar.gz numbat-`date +%Y%m%d`-svn.tar.gz

wimax: util ipv6
	$(MAKE) -C wimax

ipv6: util
	$(MAKE) -C ipv6

util:
	$(MAKE) -C util

clean:
	cd wimax; $(MAKE) clean
	cd util; $(MAKE) clean
	cd ipv6; $(MAKE) clean

.PHONY: tags wimax clean ipv6 util
