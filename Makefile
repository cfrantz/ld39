.PHONY: clean all
.PRECIOUS: *.o

all: lildigger.nes
NESLIB=/usr/local/cc65/share/cc65/lib/nes.lib

SRCS=main.c entity.c nesutil.c chars.c sprites.c screen.c levels.c
OBJS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)

clean:
	@rm -fv $(OBJS) $(ASMS) crt0-mmc3.o lildigger.nes

crt0-mmc3.o: crt0-mmc3.s neslib-mmc3.s
	ca65 crt0-mmc3.s

%.o: %.c
	cc65 -Oi $< --add-source
	ca65 $*.s

lildigger.nes: nes-mmc3.cfg crt0-mmc3.o $(OBJS)
	ld65 -C nes-mmc3.cfg --mapfile lildigger.map -o $@ \
		crt0-mmc3.o \
		$(OBJS) \
		$(NESLIB)
