
CC = /opt/riscv32i/bin/riscv32-unknown-elf-gcc
CC_DESKTOP = gcc

SMALL = rv32i
BIG = rv32im

SRC = 
LIBS = ../../_libs
#~ PROG = ./square_mmult/

INC = -I$(LIBS)

# CFLAGS

OPT = O0
WARN = Wall

OTHER = -pedantic -ffreestanding -fstack-usage

CFLAGS = -$(WARN) -$(OPT) $(OTHER) $(INC)
#~ CFLAGS = -$(WARN) $(OTHER) $(INC)

# LINKER

LINK = -Ttext 0 -Wl,-e,my_start

.PHONY: clean rv32i rv32im

rv32i: ARCH=$(SMALL)
rv32i: $(ARCH)_main.hex $(ARCH)_code

rv32im: ARCH=$(BIG)
rv32im: $(ARCH)_main.hex $(ARCH)_code

$(ARCH)_code: $(ARCH)_main.elf
	/opt/riscv32i/bin/riscv32-unknown-elf-objdump -S ./$(ARCH)_main.elf > $(ARCH)_main.objdump
	/opt/riscv32i/bin/riscv32-unknown-elf-objdump -t ./$(ARCH)_main.elf > $(ARCH)_main.objdump_table

$(ARCH)_main.hex: $(ARCH)_main.bin
	python3 ../../../tools/freedom-bin2hex.py --bit-width 32 ./$(ARCH)_main.bin > $(ARCH)_main.hex

$(ARCH)_main.bin: $(ARCH)_main.elf
	/opt/riscv32i/bin/riscv32-unknown-elf-objcopy ./$(ARCH)_main.elf -O binary ./$(ARCH)_main.bin

$(ARCH)_main.elf:
#~ 	$(CC) -march=$(ARCH) $(CFLAGS) -nostartfiles -o ./$(ARCH)_main.elf $(LINK) ../sp_nostart.S -DSTACK_POINTER=$(STACK_POINTER) ../start.S $(SRC) ./main.c
	$(CC) -march=$(ARCH) $(CFLAGS) -nostartfiles -o ./$(ARCH)_main.elf $(LINK) ../sp.S -DSTACK_POINTER=$(STACK_POINTER) ../crt0.o ../start.S $(SRC) ./main.c

clean:
	rm -f main.elf main.bin main.hex main.map *.objdump *.objdump_table *.su *.o rv32*
