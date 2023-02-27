#Add directories to search for library files
LIB := ./Core/Inc ./inc
LIB := $(addprefix -I, $(LIB))

#Compiler and linker setup
DEFINES =
CFLAGS = -Og -mcpu=cortex-m3 -mthumb -Wall -g -Wa,-a,-ad $(LIBHEADERS) $(LIB) $(DEFINES)
LINKERFLAGS = -fdata-sections -ffunction-sections -lc -lm -lnosys -specs=nano.specs -Wl,--gc-sections -specs=nosys.specs
PREF = arm-none-eabi-
COMPILER = gcc

#Main program and output directory setup
BUILDDIR = output
SRCDIR = src
INCLDIR = inc

#required ext lib targets
LIBTARGETS =

#required user lib targets
ULIBTARGETS = circ_buffer.o inits.o interrupts.o

FINALOBJ := main.o startup.o $(ULIBTARGETS) $(LIBTARGETS)
FINALOBJ := $(addprefix $(BUILDDIR)/, $(FINALOBJ))


$(BUILDDIR)/output.elf : $(FINALOBJ) linker.ld
	$(PREF)$(COMPILER) $(CFLAGS) $(LINKERFLAGS) $(FINALOBJ) -T linker.ld -o $@

$(BUILDDIR)/main.o : main.c $(INCLDIR)/$(addsuffix .h, $(basename $(ULIBATRGETS)))
	$(PREF)$(COMPILER) -c $(CFLAGS) main.c -o $@

$(BUILDDIR)/startup.o : startup.s
	$(PREF)$(COMPILER) -c $(CFLAGS) startup.s -o $@

$(addprefix $(BUILDDIR)/, $(ULIBTARGETS)) : $(BUILDDIR)/%.o : $(SRCDIR)/%.c $(INCLDIR)/%.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $< -o $@

$(addprefix $(BUILDDIR)/, $(LIBTARGETS)) : $(BUILDDIR)/%.o : $(LIB)/Source/%.c $(LIB)/Include/%.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm $(BUILDDIR)/*
