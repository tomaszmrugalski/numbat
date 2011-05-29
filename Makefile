#
# OMNeT++/OMNEST Makefile for numbat
#
# This file was generated with the command:
#  opp_makemake -f --deep --nolink -O out -d ipv6 -d util -d port-win32 -d wimax -X. -L./out/$(CONFIGNAME)/ipv6 -L./out/$(CONFIGNAME)/util -L./out/$(CONFIGNAME)/port-win32 -L./out/$(CONFIGNAME)/wimax
#

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target

all:  submakedirs Makefile
	@# Do nothing

submakedirs:  ipv6_dir util_dir port__win32_dir wimax_dir

.PHONY: ipv6 util port__win32 wimax
ipv6: ipv6_dir
util: util_dir
port__win32: port__win32_dir
wimax: wimax_dir

ipv6_dir:
	cd ipv6 && $(MAKE)

util_dir:
	cd util && $(MAKE)

port__win32_dir:
	cd port-win32 && $(MAKE)

wimax_dir:
	cd wimax && $(MAKE)

msgheaders:
	cd ipv6 && $(MAKE) msgheaders
	cd util && $(MAKE) msgheaders
	cd port-win32 && $(MAKE) msgheaders
	cd wimax && $(MAKE) msgheaders

clean:
	-rm -rf $O
	-rm -f numbat numbat.exe libnumbat.so libnumbat.a libnumbat.dll libnumbat.dylib

	-cd ipv6 && $(MAKE) clean
	-cd util && $(MAKE) clean
	-cd port-win32 && $(MAKE) clean
	-cd wimax && $(MAKE) clean

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	-cd ipv6 && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd util && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd port-win32 && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd wimax && if [ -f Makefile ]; then $(MAKE) depend; fi

