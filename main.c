#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nesutil.h"
#include "screen.h"
#include "entity.h"

const unsigned char palette[32]={
	// Background palette
	0x22, 0x03, 0x23, 0x30,
	0x0f, 0x11, 0x21, 0x30,
    0x0f, 0x07, 0x17, 0x0f,
    0x0f, 0x0a, 0x1a, 0x0f,

	// Sprite palette
	0x0F, 0x02, 0x07, 0x26,
	0x0F, 0x16, 0x2d, 0x0f,
	0x0F, 0x02, 0x11, 0x20,
	0x0F, 0x19, 0x29, 0x39,
};

uint8_t tm;
uint8_t val;
uint16_t reg;
uint16_t framenum;
uint8_t spr;
uint8_t a;
uint8_t dude[] = { 1, 3, 1, 3 };

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
	oam_size(1);

    copy_to_vram_simple(0);
	ppu_on_all();//enable rendering

    entity_set_player(128, 144);
    entity_new(1, 224, 16);
    //tm = readreg8(0x401b);
    a = 0;
	for(;;++framenum) {
		//wait for next TV frame
        entity_load_screen();
		ppu_waitnmi();
        entity_newframe();

        entity_player_control();
    tm = readreg8(0x4019);
        entity_compute_position(0);
        entity_update_all();
    tm = readreg8(0x4019);
        entity_draw(0);
        entity_draw_all();

#if 0
        if ((framenum & 7) == 0) {
            if (++a == 4) a = 0;
        }
        spr = oam_spr(20, 40, dude[a], 0, spr);
        val = spr;

        update_reset();
        update(0, 10, xdigits[(uint8_t)framenum >> 4]);
        update(1, 10, xdigits[(uint8_t)framenum & 15]);
#endif
    }
}
