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
	0x0F, 0x2c, 0x28, 0x30,
};

uint8_t tm;
uint8_t val;
uint16_t reg;
uint16_t framenum;
uint8_t spr;
uint8_t a;

uint8_t player_pad;
uint8_t player_pad_changed;
uint8_t spridx;
enum GameMode {
    TITLE_SCREEN,
    GAME,
    PAUSE,
};

enum GameMode game_state;

void pause(void) {
    static uint8_t x, y;

    x = 104; y = 6*16;
    spridx = oam_spr(x, y, 0xd1, 3, spridx); x+= 8;
    spridx = oam_spr(x, y, 0xd3, 3, spridx); x+= 8;
    spridx = oam_spr(x, y, 0xd5, 3, spridx); x+= 8;
    spridx = oam_spr(x, y, 0xd7, 3, spridx); x+= 8;
    spridx = oam_spr(x, y, 0xd9, 3, spridx);
}

void main(void)
{
    bank_bg(0);
    bank_spr(1);
	set_vram_update(PER_FRAME_PPU_UPDATE_LENGTH, update_list);
	ppu_off();
	pal_all(palette);//set palette for sprites
	oam_size(1);

    // Will load the first screen and turn the ppu on
    //tm = readreg8(0x401b);
    ppu_off();
    entity_load_screen();
	for(;;++framenum) {
		//wait for next TV frame
		ppu_waitnmi();
        oam_clear();
        player_pad_changed = pad_trigger(0);
        player_pad = pad_state(0);

        switch(game_state) {
            case TITLE_SCREEN:
                entity_newframe();
                entity_set_player(128, 160);
                entity_update_all();
                entity_draw(0);
                entity_draw_all();

                if (player_pad_changed & PAD_START) {
                    game_state = GAME;
                    ppu_off();
                    entity_set_screen(1);
                    entity_load_screen();
                }
                break;
            case GAME:
                entity_newframe();
                entity_player_control();
                // tm = readreg8(0x4019);
                entity_update_all();
                entity_compute_position(0);
                // tm = readreg8(0x4019);
                entity_draw(0);
                entity_draw_all();
                entity_draw_stats();
                entity_check_load_screen();
                if (player_pad_changed & PAD_START)
                    game_state = PAUSE;
                break;
            case PAUSE:
                pause();
                entity_draw(0);
                entity_draw_all();
                if (player_pad_changed & PAD_START)
                    game_state = GAME;
                break;
            default:
                game_state = GAME;
        }
    }
}
