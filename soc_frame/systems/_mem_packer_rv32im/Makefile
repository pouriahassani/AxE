######################################################################
#
# DESCRIPTION: Verilator Example: Small Makefile
#
# This calls the object directory makefile.  That allows the objects to
# be placed in the "current directory" which simplifies the Makefile.
#
# Copyright 2003-2019 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# Lesser General Public License Version 3 or the Perl Artistic License
# Version 2.0.
#
######################################################################
# Check for sanity to avoid later confusion

ifneq ($(words $(CURDIR)),1)
 $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

######################################################################

# This is intended to be a minimal example.  Before copying this to start a
# real project, it is better to start with a more complete example,
# e.g. examples/tracing_c.

# If $VERILATOR_ROOT isn't in the environment, we assume it is part of a
# package inatall, and verilator is in your path. Otherwise find the
# binary relative to $VERILATOR_ROOT (such as when inside the git sources).
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

VERILATOR_FLAGS =
VERILATOR_FLAGS += -cc --exe

# used to create trace file
VERILATOR_FLAGS += --trace

# used to dump large arrays
#VERILATOR_FLAGS += --trace-max-array 10200
#~ VERILATOR_FLAGS += --trace-max-array 8192
#~ VERILATOR_FLAGS += --trace-max-array 2048
VERILATOR_FLAGS += --trace-max-array 20480000

# Disable fatal exit on warnings
# pico causes some warnings and this is needed so the warnings don't cause an
# exit
VERILATOR_FLAGS += -Wno-fatal

# adding a directory
#~ VERILATOR_FLAGS += -y ../../rtl/noc/noc_connect_16

######################################################################
# 
# rtl
# 
######################################################################

.PHONY: compile run wave clean

default: compile

obj_dir/Vtop:
	$(VERILATOR) $(VERILATOR_FLAGS) top.sv sim_main.cpp
	$(MAKE) -j 4 -C obj_dir -f Vtop.mk

compile: obj_dir/Vtop

run: obj_dir/Vtop
	obj_dir/Vtop 0

wave: obj_dir/Vtop
	obj_dir/Vtop +trace
	gtkwave logs/vlt_dump.vcd --script=gtkwave.tcl

clean:
	-rm -rf logs obj_dir *.log *.dmp *.vpd core

