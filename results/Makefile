DIRS=run1 run2 run3 run4 run5 run6 run7 run8 run9 runA

all: split

split:
	for dir in $(DIRS); do           \
		cp -f $$dir.vec $$dir/ ; \
		echo "Going to $$dir";   \
		cd $$dir;                \
		splitvecth $$dir.vec;      \
		cd ..;                   \
	done

.PHONY: all diagram1 diagram2 diagram3 diagram4 diagram5 diagram6 diagram7 diagram8 diagram9

dirs:
	for dir in $(DIRS); do \
		echo "Creating $$dir directory."; \
		mkdir $$dir; \
	done

DIAGRAMPATTERN1 = "DHCP conf. time"
DIAGRAMPATTERN2 = 'ssIPv6.*"IPv6Node Received Packets"'
DIAGRAMPATTERN3 = "DHCP conf. complete"
DIAGRAMPATTERN4 = "HO Preparation time"
DIAGRAMPATTERN5 = "HO Reentry time"
DIAGRAMPATTERN6 = "HO IP reconfigure time"
DIAGRAMPATTERN7 = "HO Lack of comm. capab. time"
DIAGRAMPATTERN8 = 'CN.*"IPv6Node Received Packets"'
DIAGRAMPATTERN9 = 'AvgDelayVector'

diagram1:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN1) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram2:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN2) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram3:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN3) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram4:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN4) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram5:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN5) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram6:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN6) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram7:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN7) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram8:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN8) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@
diagram9:
	mkdir $@; rm -f $@/*; rm -f tmp
	for dir in $(DIRS); do grep -l -e $(DIAGRAMPATTERN9) $$dir/$$dir-*.vec >> tmp; done
	./copyfiles tmp $@

diagrams: diagram1 diagram2 diagram3 diagram4 diagram5 diagram6 diagram7 diagram8 diagram9

clean:
	for dir in $(DIRS); do \
		echo "Cleanup in $$dir";\
		cd $$dir; rm -f *.vec; cd ..;\
	done
