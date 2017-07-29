.PHONY: clean all
.PRECIOUS: *.o

all: mmc3check.nes
NESLIB=/usr/local/cc65/share/cc65/lib/nes.lib

SRCS=mmc3check.c entity.c nesutil.c chars.c sprites.c screen.c
OBJS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)

clean:
	@rm -fv $(OBJS) $(ASMS) crt0-mmc3.o mmc3check.nes

crt0-mmc3.o: crt0-mmc3.s neslib-mmc3.s
	ca65 crt0-mmc3.s

%.o: %.c
	cc65 -Oi $< --add-source
	ca65 $*.s

mmc3check.nes: nes-mmc3.cfg crt0-mmc3.o $(OBJS)
	ld65 -C nes-mmc3.cfg --mapfile mmc3check.map -o $@ \
		crt0-mmc3.o \
		$(OBJS) \
		$(NESLIB)
