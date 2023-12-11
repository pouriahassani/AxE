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

#~ CONFIGURATION = single
#~ CONFIGURATION = single_mem_packer
#~ CONFIGURATION = single_mem_packer_rv32im
#~ CONFIGURATION = mult
#~ CONFIGURATION = noc_one_node
#~ CONFIGURATION = mult_noc_interface
CONFIGURATION = test_single_vivado

#~ CONFIGURATION = noc_one_node_2_different_connection
#~ CONFIGURATION = noc_two_nodes
#~ CONFIGURATION = noc_three_nodes
#~ CONFIGURATION = mult_no_noc_interface
#~ CONFIGURATION = mult_noc_interface
#~ CONFIGURATION = test

DIR = ./configurations/$(CONFIGURATION)

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
# --threads {4}

# used to dump large arrays
#~ VERILATOR_FLAGS += --trace-max-array 10200
#~ VERILATOR_FLAGS += --trace-max-array 8192
#~ VERILATOR_FLAGS += --trace-max-array 2048

# Disable fatal exit on warnings
# pico causes some warnings and this is needed so the warnings don't cause an
# exit
VERILATOR_FLAGS += -Wno-fatal

# adding a directory
VERILATOR_FLAGS += -y rtl/noc/noc_connect_16

######################################################################
# 
# rtl
# 
######################################################################

.PHONY: run wave sw clean_sw programs clean_programs controller clean_controller

#~ default: compile sw controller

default:
	$(MAKE) -C $(DIR)

run:
	$(MAKE) -C $(DIR) run

wave:
	$(MAKE) -C $(DIR) wave

clean:
	$(MAKE) -C $(DIR) clean

######################################################################
# 
# sw
# 
######################################################################

sw: programs controller

clean_sw: clean_programs clean_controller

programs:
	$(MAKE) -C sw/programs/aes/ big
	$(MAKE) -C sw/programs/msort/ big
	$(MAKE) -C sw/programs/blowfish/ big
	$(MAKE) -C sw/programs/dhrystone/ big
	$(MAKE) -C sw/programs/norx/ big
	$(MAKE) -C sw/programs/primes/ big
	$(MAKE) -C sw/programs/qsort/ big
	$(MAKE) -C sw/programs/sha256/ big
	$(MAKE) -C sw/programs/square_mmult/ big
	$(MAKE) -C sw/programs/mul/ big
	$(MAKE) -C sw/programs/aes/ small
	$(MAKE) -C sw/programs/msort/ small
	$(MAKE) -C sw/programs/blowfish/ small
	$(MAKE) -C sw/programs/dhrystone/ small
	$(MAKE) -C sw/programs/norx/ small
	$(MAKE) -C sw/programs/primes/ small
	$(MAKE) -C sw/programs/qsort/ small
	$(MAKE) -C sw/programs/sha256/ small
	$(MAKE) -C sw/programs/square_mmult/ small
	$(MAKE) -C sw/programs/mul/ small

clean_programs:
	$(MAKE) -C sw/programs/aes/ clean
	$(MAKE) -C sw/programs/msort/ clean
	$(MAKE) -C sw/programs/blowfish/ clean
	$(MAKE) -C sw/programs/dhrystone/ clean
	$(MAKE) -C sw/programs/norx/ clean
	$(MAKE) -C sw/programs/primes/ clean
	$(MAKE) -C sw/programs/qsort/ clean
	$(MAKE) -C sw/programs/sha256/ clean
	$(MAKE) -C sw/programs/square_mmult/ clean
	$(MAKE) -C sw/programs/mul/ clean

controller:
	$(MAKE) -C sw/controller/ big

clean_controller:
	$(MAKE) -C sw/controller/ clean
