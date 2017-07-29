.PHONY: clean all

.PRECIOUS: *.o

NESLIB=/usr/local/cc65/share/cc65/lib/nes.lib

SRCS=scrolldemo.c starfield.c ftrig.c chars.c tiles.c
OBJS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)

clean:
	@rm -fv $(OBJS) $(ASMS) crt0.o scrolldemo.nes

crt0-mmc3.o: crt0-mmc3.s neslib-mmc3.s
	ca65 crt0-mmc3.s

%.o: %.c
	cc65 -Oi $< --add-source
	ca65 $*.s

mmc3check.nes: mmc3check.o nesutil.o crt0-mmc3.o unscii/unscii.o unscii/mcr.o nes-mmc3.cfg
	ld65 -C nes-mmc3.cfg --mapfile mmc3check.map -o $@ \
		crt0-mmc3.o \
		mmc3check.o \
		nesutil.o \
		unscii/unscii.o \
		unscii/mcr.o \
		$(NESLIB)
