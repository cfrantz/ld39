#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nesutil.h"

const unsigned char palette[32]={
	// Background palette
	0x0F,0x03,0x23,0x30,
	0x0F,0x11,0x21,0x30,
	0x0F,0x15,0x25,0x30,
	0x0F,0x19,0x29,0x30,

	// Sprite palette
	0x0F,0x00,0x10,0x20,
	0x0F,0x11,0x21,0x31,
	0x0F,0x02,0x11,0x20,
	0x0F,0x19,0x29,0x39,
};

uint8_t tm;
uint8_t val;
uint16_t reg;
uint16_t framenum;
uint8_t spr;

void chrset() {
    uint8_t x, y, i;
    for(y=0; y<16; y++) {
        for(x=0; x<16; x++) {
            vram_adr(VADDR(x+8, y+4));
            vram_put( (y<<4) | x );
        }
    }
	vram_puts(8, 21, __TIME__);
	vram_puts(0, 32+3, "+------------------------------+");
	for(i=4; i<28; i++)
		vram_puts(0, 32+i, "|                              |");
	vram_puts(0, 32+28, "+------------------------------+");
                  // 0         1         2         3
                  // 01234567890123456789012345678901
    vram_puts(0, 1, "The quick brown fox jumped over_");
    vram_puts(0, 2, "the lazy dog!___________________");
}

void __fastcall__ sprite0hit_scroll(void);

void main(void)
{
    bank_bg(0);
    bank_spr(1);
	set_vram_update(PER_FRAME_PPU_UPDATE_LENGTH, update_list);
	ppu_off();
	pal_all(palette);//set palette for sprites
	oam_size(0);

    chrset();
	ppu_on_all();//enable rendering
    writereg8(0xc000, 24);
    writereg8(0xc001, 24);
    writereg8(0xe001, 24);

    tm = readreg8(0x401b);
	for(;;++framenum) {
		//wait for next TV frame
		ppu_waitnmi();
        tm = readreg8(0x401b);
        val = readreg8(0x1f);
        while(val == readreg8(0x1f))
            ;

        scroll(framenum, framenum/2);

        update_reset();
        update(0, 10, xdigits[(uint8_t)framenum >> 4]);
        update(1, 10, xdigits[(uint8_t)framenum & 15]);
        update(0, 32+10, xdigits[(uint8_t)framenum >> 4]);
        update(1, 32+10, xdigits[(uint8_t)framenum & 15]);

        update(0, 11, xdigits[val >> 4]);
        update(1, 11, xdigits[val & 15]);
        update(0, 32+11, xdigits[val >> 4]);
        update(1, 32+11, xdigits[val & 15]);

    }
}
