GENDEV = /opt/toolchains/sega

CC = $(GENDEV)/m68k-elf/bin/m68k-elf-gcc
AS = $(GENDEV)/m68k-elf/bin/m68k-elf-as
OBJC = $(GENDEV)/m68k-elf/bin/m68k-elf-objcopy
RM = rm -f
ASMZ80 = zasm
BINTOC = bin2c

OPTION = --std=c11
INCLUDES = -Iinclude
CCFLAGS = $(OPTION) -m68000 -Wall -O2 -c -fomit-frame-pointer
HWCCFLAGS = $(OPTION) -m68000 -Wall -O1 -c -fomit-frame-pointer
Z80FLAGS = -vb2
ASFLAGS = -Iresource -m68000 --register-prefix-optional
LIBS = -L$(GENDEV)/m68k-elf/lib -L$(GENDEV)/m68k-elf/m68k-elf/lib -lc -lgcc -lnosys
LINKFLAGS = -T $(GENDEV)/ldscripts/md.ld -Wl,-Map=output.map -nostdlib

SRCS_C = $(wildcard src/*.c src/resource/*.c)
SRCS_S = $(wildcard src/*.s)

# Order matters here and boot.s must be the first file!
OBJS = boot/boot.o $(SRCS_C:.c=.o) $(SRCS_S:.s=.o)

all: Concordia.bin

Concordia.bin: Concordia.elf
	$(OBJC) -O binary $< temp.bin
	dd if=temp.bin of=$@ bs=8K conv=sync
	rm temp.bin Concordia.elf

Concordia.elf: $(OBJS)
	$(CC) $(LINKFLAGS) $(OBJS) $(LIBS) -o Concordia.elf

%.o80: %.s80
	$(ASMZ80) $(Z80FLAGS) -o $@ $<

%.c: %.o80
	$(BINTOC) $<

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) *.o *.bin *.elf *.map
	find src/ -name "*.o" -type f -delete
	find boot/ -name "*.o" -type f -delete
