#include <stdio.h>
#include <stdint.h>
#include "bcd.h"
#include "entity.h"
#include "levels.h"
#include "screen.h"
#include "nesutil.h"

//////////////////////////////////////////////////////////////////////
// The following are parameters indexed on entity id
//
// Even ids are 8x16 sprites
// Odd ids are 16x16 sprites
//
// 0: player
// 1: snake
// 2: key
// 3: spider
// 4: gold
// 5: locked door
// 6: energy crystal
// 7: checkpoint 
// 8: ??? 
// 9: endpoint
//////////////////////////////////////////////////////////////////////

const uint8_t entity_palette[] = {  0, 1, 3, 1, 3, 3, 3, 0, 0, 1,};
const uint8_t entity_physics[] = {  1, 0, 0, 1, 0, 0, 0, 1, 0, 0,};

//                                  0  1   2   3   4   5   6   7   8   9
const uint8_t entity_colx_x0[] = {  1, 0,  0,  0,  0,  0,  0,  0,  0,  0, };
const uint8_t entity_colx_y0[] = {  2, 2,  8,  2,  4,  0,  1,  0,  0,  0, };
const uint8_t entity_colx_x1[] = {  6, 14, 0,  16, 8,  16, 8,  15, 0,  15, };
const uint8_t entity_colx_y1[] = { 14, 14, 15, 14, 15, 16, 14, 15, 0,  15, };

const uint8_t entity_coly_x0[] = {  2, 0,  0,  2,  0,  1,  0,  0,  0,  0, };
const uint8_t entity_coly_y0[] = {  0, 2,  8,  2,  4,  1,  1,  0,  0,  0, };
const uint8_t entity_coly_x1[] = {  5, 14, 0,  14, 8,  15, 8,  15, 0,  15, };
const uint8_t entity_coly_y1[] = { 16, 16, 15, 16, 15, 15, 14, 15, 0,  15, };

const int entity_maxx[] = {
    0x180, 0x200, 0x000, 0x100, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
};

const int entity_maxy[] = {
    0x500, 0x500, 0x000, 0x500, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
};

const uint8_t entity_sprites[][4] = {
    { 1, 3, 1, 3 },
    { 0x11, 0x15, 0x11, 0x15 },
    { 0x0b, 0x0b, 0x0b, 0x0b },
    { 0x19, 0x19, 0x1d, 0x1d },
    { 0x0d, 0x0d, 0x0f, 0x0f },
    { 0x21, 0x21, 0x21, 0x21 },
    { 0x25, 0x25, 0x27, 0x27 },
    { 0x29, 0x29, 0x29, 0x29 },
    { 0, 0, 0, 0 },
    { 0x29, 0x29, 0x29, 0x29 },
};

const uint8_t bittable[8] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
};

//////////////////////////////////////////////////////////////////////
// The following are per-active-entity state, indexed on active
// entities.  Entity zero is always the player.
//
//////////////////////////////////////////////////////////////////////
uint8_t entity_id[MAX_ENTITY];
uint16_t entity_px[MAX_ENTITY];
uint16_t entity_py[MAX_ENTITY];

int16_t entity_ax[MAX_ENTITY];
int16_t entity_ay[MAX_ENTITY];

int16_t entity_vx[MAX_ENTITY];
int16_t entity_vy[MAX_ENTITY];
uint8_t entity_on_ground[MAX_ENTITY];

int8_t entity_dir[MAX_ENTITY];
uint8_t entity_anim[MAX_ENTITY];
uint8_t entity_sprite_id[MAX_ENTITY];
uint8_t entity_sprite_attr[MAX_ENTITY];

#pragma data-name(push, "MORERAM")
uint8_t entity_taken[256];
#pragma data-name(pop)

//////////////////////////////////////////////////////////////////////
// The various collision detection functions in this module use the following
// globals as parameter registers.
//////////////////////////////////////////////////////////////////////
static uint8_t cur_id;
static uint8_t cur_index;
static uint16_t px, py;
static uint8_t xx, yy;

//////////////////////////////////////////////////////////////////////
// The following have player state information
//////////////////////////////////////////////////////////////////////

extern uint8_t player_pad;
extern uint8_t player_pad_changed;;
extern uint8_t spridx;
extern uint8_t player_room;
extern uint8_t player_rx, player_ry;
uint8_t player_state;
uint8_t player_jump;
uint8_t player_ckpt_x, player_ckpt_y;
uint8_t player_ckpt_rx, player_ckpt_ry;
uint8_t player_ckpt_room;
uint8_t player_hit;
uint8_t player_inv;
uint8_t player_keys;
uint16_t player_score;
uint16_t player_energy;
uint8_t player_etick;

uint8_t __fastcall__ entity_left_collision(int16_t delta) {
    xx = (px + delta) >> 8;
    xx += entity_colx_x0[cur_id];
    yy = entity_py[cur_index] >> 8;
    if (basic_collision(xx, yy + entity_colx_y0[cur_id]) ||
        basic_collision(xx, yy + entity_colx_y1[cur_id])) {
        return xx & 0xf0;
    }
    return 0xff;
}

uint8_t __fastcall__ entity_right_collision(int16_t delta) {
    xx = (px + delta) >> 8;
    xx += entity_colx_x1[cur_id];
    yy = entity_py[cur_index] >> 8;
    if (basic_collision(xx, yy + entity_colx_y0[cur_id]) ||
        basic_collision(xx, yy + entity_colx_y1[cur_id])) {
        return xx & 0xf0;
    }
    return 0xff;
}

uint8_t __fastcall__ entity_top_collision(int16_t delta) {
    yy = (py + delta) >> 8;
    yy += entity_coly_y0[cur_id];
    xx = entity_px[cur_index] >> 8;
    if (basic_collision(xx + entity_coly_x0[cur_id], yy) ||
        basic_collision(xx + entity_coly_x1[cur_id], yy)) {
        return yy & 0xf0;
    }
    return 0xff;
}

uint8_t __fastcall__ entity_bottom_collision(int16_t delta) {
    yy = (py + delta) >> 8;
    yy += entity_coly_y1[cur_id];
    xx = entity_px[cur_index] >> 8;
    if (basic_collision(xx + entity_coly_x0[cur_id], yy) ||
        basic_collision(xx + entity_coly_x1[cur_id], yy)) {
        return yy & 0xf0;
    }
    return 0xff;
}

uint8_t __fastcall__ entity_player_collision(void) {
    static uint8_t px0, px1, py0, py1;
    static uint8_t ex0, ex1, ey0, ey1;

    xx = entity_px[0] >> 8;
    yy = entity_py[0] >> 8;
    px0 = xx + entity_colx_x0[0];
    py0 = yy + entity_colx_y0[0];
    px1 = xx + entity_colx_x1[0];
    py1 = yy + entity_colx_y1[0];

    xx = entity_px[cur_index] >> 8;
    yy = entity_py[cur_index] >> 8;
    ex0 = xx + entity_colx_x0[cur_id];
    ey0 = yy + entity_colx_y0[cur_id];
    ex1 = xx + entity_colx_x1[cur_id];
    ey1 = yy + entity_colx_y1[cur_id];

    return !(ex1 < px0 || ey1 < py0 || ex0 > px1 || ey0 > py1);
}

void __fastcall__ entity_player_knockback(uint16_t ax, uint16_t dmg) {
    if (!player_inv) {
        if (entity_dir[0] > 0) {
            entity_ax[0] = -ax;
        } else {
            entity_ax[0] = ax;
        }
        entity_ay[0] = -0x180;
        player_inv = 90;
        player_hit = 30;
        player_energy = bcd_add16(player_energy, dmg);
    }
}

void __fastcall__ entity_compute_position_x(void) {
    static uint8_t c;
    static int16_t vx;

    vx = entity_vx[cur_index];
    px = entity_px[cur_index];
    if (vx > 0) {
        c = entity_right_collision(vx);
        if (c != 0xff) {
            entity_px[cur_index] = (c - entity_colx_x1[cur_id]) << 8;
            entity_vx[cur_index] = 0;
        } else {
            px += vx;
            entity_px[cur_index] = px;
        }
        c = entity_left_collision(0);
        if (c != 0xff) {
            entity_px[cur_index] = (c + 0x10 - entity_colx_x0[cur_id]) << 8;
        }
    } else {
        c = entity_left_collision(vx);
        if (c != 0xff) {
            entity_px[cur_index] = (c + 0x10 - entity_colx_x0[cur_id]) << 8;
            entity_vx[cur_index] = 0;
        } else {
            px += vx;
            entity_px[cur_index] = px;
        }
        c = entity_right_collision(0);
        if (c != 0xff) {
            entity_px[cur_index] = (c - entity_colx_x1[cur_id]) << 8;
        }
    }
}

void __fastcall__ entity_compute_position_y(void) {
    static uint8_t c;
    static int16_t vy;

    vy = entity_vy[cur_index];
    py = entity_py[cur_index];
    entity_on_ground[cur_index] &= 0xFE;
    if (vy > 0) {
        c = entity_bottom_collision(vy);
        if (c != 0xff) {
            entity_py[cur_index] = (c - entity_coly_y1[cur_id]) << 8;
            entity_vy[cur_index] = 0;
            entity_on_ground[cur_index] |= 1;
        } else {
            py += vy;
            entity_py[cur_index] = py;
        }
        c = entity_top_collision(0);
        if (c != 0xff) {
            entity_py[cur_index] = (c + 0x10 - entity_coly_y0[cur_id]) << 8;
        }
    } else {
        c = entity_top_collision(vy);
        if (c != 0xff) {
            entity_py[cur_index] = (c + 0x10 - entity_coly_y0[cur_id]) << 8;
            entity_vy[cur_index] = 0;
        } else {
            py += vy;
            entity_py[cur_index] = py;
        }
        c = entity_bottom_collision(0);
        if (c != 0xff) {
            entity_py[cur_index] = (c - entity_coly_y1[cur_id]) << 8;
        }
    }
}


void __fastcall__ entity_compute_position(uint8_t entity) {
    static int16_t vx, vy, fx;

    cur_index = entity;
    cur_id = entity_id[cur_index];
    fx = 0;
    if (entity_on_ground[cur_index])
        fx = 0x0040;

    vx = entity_vx[cur_index];
    vy = entity_vy[cur_index];

    if (cur_index == 0) {
        if (player_state == PLAYER_DEAD)
            return;

        if (!(player_pad & (PAD_LEFT | PAD_RIGHT))) {
            if (vx > 0)
                vx -= fx;
            else if (vx < 0)
                vx += fx;
        }
    }

    vx += entity_ax[cur_index];
    vy += entity_ay[cur_index];

    if (vx > entity_maxx[cur_id]) {
        vx = entity_maxx[cur_id];
    } else if (vx < -entity_maxx[cur_id]) {
        vx = -entity_maxx[cur_id];
    }
    if (vy > entity_maxy[cur_id]) {
        vy = entity_maxy[cur_id];
    } else if (vy < -entity_maxy[cur_id]) {
        vy = -entity_maxy[cur_id];
    }

    entity_vx[cur_index] = vx;
    entity_vy[cur_index] = vy;

    entity_compute_position_x();
    entity_compute_position_y();
}

void __fastcall__ entity_newframe(void) {
    spridx = 0;
    for(cur_index=0; cur_index<MAX_ENTITY; ++cur_index) {
        entity_ay[cur_index] = 0x100;
    }
}

void __fastcall__ entity_taken_reset(void) {
    uint8_t y;
    y = 0;
    do {
        entity_taken[y] = 0;
    } while(++y);
}

void __fastcall__ entity_draw(uint8_t index) {
    static uint8_t id, sprid, attr;
    id = entity_id[index];

    if (id == 0 && (player_inv & 2))
        return;

    xx = entity_px[index] >> 8;
    yy = entity_py[index] >> 8;
    sprid = entity_sprite_id[index];
    attr = entity_sprite_attr[index];

    if (id & 1) {
        // Entities with odd id's are 2x wide
        if (entity_dir[index] > 0) {
            spridx = oam_spr(xx, yy, sprid+2, attr, spridx);
            spridx = oam_spr(xx+8, yy, sprid, attr, spridx);
        } else {
            spridx = oam_spr(xx, yy, sprid, attr, spridx);
            spridx = oam_spr(xx+8, yy, sprid+2, attr, spridx);
        }
    } else {
        spridx = oam_spr(xx, yy, sprid, attr, spridx);
    }

}

void __fastcall__ entity_draw_stats(void) {
#if 0
    static uint16_t en;
    spridx = oam_spr(16, 8, 0x0b, 3, spridx);
    spridx = oam_spr(24, 8, 0xe1 + player_keys * 2, 3, spridx);


    en = player_energy;
    spridx = oam_spr(40, 8, 0x25, 3, spridx);
    spridx = oam_spr(72, 8, 0xe1 + (en & 0x0F) * 2, 3, spridx);
    en >>= 3;
    spridx = oam_spr(64, 8, 0xe1 + (en & 0x1E), 3, spridx);
    en >>= 4;
    spridx = oam_spr(56, 8, 0xe1 + (en & 0x1E), 3, spridx);
    en >>= 4;
    spridx = oam_spr(48, 8, 0xe1 + (en & 0x1E), 3, spridx);
#endif
    extern uint8_t hud[32];
    static uint8_t val;
    hud[5] = 0x30 + player_keys;

    val = player_energy;
    hud[18] = 0x30 + (val & 0x0F); val >>= 4;
    hud[17] = 0x30 + (val & 0x0F);
    val = player_energy >> 8;
    hud[16] = 0x30 + (val & 0x0F); val >>= 4;
    hud[15] = 0x30 + (val & 0x0F);

    hud[31] = 0x30;
    val = player_score;
    hud[30] = 0x30 + (val & 0x0F); val >>= 4;
    hud[29] = 0x30 + (val & 0x0F); 
    val = player_score >> 8;
    hud[28] = 0x30 + (val & 0x0F); val >>= 4;
    hud[27] = 0x30 + (val & 0x0F);
}


void __fastcall__ entity_set_player(uint8_t x, uint8_t y, uint8_t chkpoint) {
    entity_ax[0] = 0;
    entity_ay[0] = 0;
    entity_vx[0] = 0;
    entity_vy[0] = 0;
    entity_px[0] = x<<8;
    entity_py[0] = y<<8;
    entity_on_ground[0] = 1;
    entity_sprite_id[0] = entity_sprites[0][0];
    player_energy = 0x200;
    player_state = PLAYER_ALIVE;
    if (chkpoint) {
        player_ckpt_x = x;
        player_ckpt_y = y;
        player_ckpt_rx = player_rx;
        player_ckpt_ry = player_ry;
        player_ckpt_room = player_room;
    }
}

void __fastcall__ entity_new(uint8_t id, uint8_t x, uint8_t y) {
    static uint8_t i;

    for(i=1; i<MAX_ENTITY; ++i) {
        if (entity_id[i] == 0) {
            entity_id[i] = id;
            entity_ax[i] = 0;
            entity_ay[i] = 0;
            entity_vx[i] = 0;
            entity_vy[i] = 0;
            entity_px[i] = x<<8;
            entity_py[i] = y<<8;
            entity_dir[i] = 0;
            entity_anim[i] = 0;
            entity_sprite_attr[i] = entity_palette[id];
            break;
        }
    }
}

void __fastcall__ entity_take(void) {
    xx = entity_px[cur_index] >> 8;
    entity_taken[player_room] |= bittable[xx>>5];
    entity_id[cur_index] = 0;
}

void __fastcall__ entity_update(void) {
    static uint8_t a;
    static int16_t delta;

    cur_id = entity_id[cur_index];
    if (entity_physics[cur_id])
        entity_compute_position(cur_index);

    a = (entity_anim[cur_index] / 4) & 3;
    if (entity_dir[cur_index] > 0) {
        entity_sprite_attr[cur_index] |= 0x40;
    } else {
        entity_sprite_attr[cur_index] &= ~0x40;
    }
    entity_sprite_id[cur_index] = entity_sprites[cur_id][a];
    ++entity_anim[cur_index];
    switch(cur_id) {
    case SNAKE:
        entity_dir[cur_index] = (entity_px[0] < entity_px[cur_index]) ? -1 : 1;
        if (entity_player_collision()) {
            // 50 points of damage
            entity_player_knockback(0x80, 0xF950);
        }
        break;
    case KEY:
        if (entity_player_collision()) {
            entity_take();
            ++player_keys;
            player_score = bcd_add16(player_score, 0x015);
        }
        break;
    case SPIDER:
        // walk towards player
        delta = (entity_px[0]>>8) - (entity_px[cur_index]>>8);
        if (delta < 0) {
            entity_ax[cur_index] = -0x40;
        } else if (delta > 0) {
            entity_ax[cur_index] = 0x40;
        } else {
            entity_ax[cur_index] = 0;
        } 
        if (entity_player_collision()) {
            // 25 points of damage
            entity_player_knockback(0x80, 0xF975);
        }
        break;
    case GOLD:
        if (entity_player_collision()) {
            entity_take();
            player_score = bcd_add16(player_score, 0x0100);
        }
        break;
    case DOOR:
        if (entity_player_collision()) {
            if (player_keys) {
                entity_take();
                --player_keys;
            } else {
                delta = entity_px[0] - entity_px[cur_index];
                if (delta < 0) {
                    // Player is left of door
                    entity_px[0] = entity_px[cur_index] - 0x800;
                } else {
                    // Player is right of door
                    entity_px[0] = entity_px[cur_index] + 0xF00;
                }
            }
        }
        break;
    case CRYSTAL:
        if (entity_player_collision()) {
            entity_take();
            player_energy = bcd_add16(player_energy, 0x0120);
        }
        break;
    case CHECKPOINT:
        if (entity_player_collision()) {
            player_ckpt_x = entity_px[0] >> 8;
            player_ckpt_y = entity_py[0] >> 8;
            player_ckpt_rx = player_rx;
            player_ckpt_ry = player_ry;
            player_ckpt_room = player_room;
        }
        break;
    case ENDPOINT:
        if (entity_player_collision()) {
            player_state = PLAYER_DONE;
        }
        break;

    default: // all others
        ;
    }
}

void __fastcall__ entity_update_all(void) {
    for(cur_index=1; cur_index<MAX_ENTITY; ++cur_index) {
        if (entity_id[cur_index] != 0) {
            entity_update();
        }
    }
}

void __fastcall__ entity_kill_all(void) {
    for(cur_index=1; cur_index<MAX_ENTITY; ++cur_index) {
        entity_id[cur_index] = 0;
    }
}

void __fastcall__ entity_draw_all(void) {
    for(cur_index=1; cur_index<MAX_ENTITY; ++cur_index) {
        if (entity_id[cur_index] != 0) {
            entity_draw(cur_index);
        }
    }
}

uint8_t __fastcall__ entity_player_addpoints(void) {
    if (player_energy) {
        player_energy = bcd_add16(player_energy, 0xF999);
        player_score = bcd_add16(player_score, 0x10);
        return true;
    }
    return false;
}

uint8_t __fastcall__ entity_player_control(void) {
    static uint8_t on_ladder, a;

    if (player_state == PLAYER_DONE)
        return player_state;

    if (player_energy==0 || player_energy & 0x8000) {
        if (player_state == PLAYER_ALIVE) {
            player_energy = 0;
            player_hit = player_inv = 180;
            entity_sprite_id[0] = 0x07;
            entity_ax[0] = 0;
            entity_ay[0] = 0;
            entity_vx[0] = 0;
            entity_vy[0] = 0;
            player_state = PLAYER_DEAD;
        }
    } else if (++player_etick == 60) {
        player_energy = bcd_add16(player_energy, 0xF999);
        player_etick = 0;
    }
    if (player_inv) --player_inv;
    if (player_hit) {
        --player_hit;
        return PLAYER_ALIVE;
    } else if (player_state == PLAYER_DEAD) {
        return PLAYER_DEAD;
    }

    a = (entity_anim[0] / 4) & 3;
    entity_sprite_attr[0] = (entity_dir[0] < 0) ? 0x40 : 0;
    entity_sprite_id[0] = entity_sprites[0][a];

    xx = entity_px[0] >> 8;
    yy = entity_py[0] >> 8;

    on_ladder = (screen_tile(xx+4, yy+0) == 1 || screen_tile(xx+4, yy+15) == 1);;
    if (on_ladder) {
        entity_ay[0] = 0;
        entity_on_ground[0] |= 2;
        entity_sprite_id[0] = 5;
        if (player_pad & PAD_DOWN) {
            entity_vy[0] = 0x100;
            entity_sprite_attr[0] = (a & 1) ? 0x40 : 0;
            ++entity_anim[0];
        } else if (player_pad & PAD_UP) {
            entity_vy[0] = -0x100;
            entity_sprite_attr[0] = (a & 1) ? 0x40 : 0;
            ++entity_anim[0];
        } else {
            entity_vy[0] = 0;
        }
    } else {
        entity_on_ground[0] &= ~2;
    }
    if (player_pad & PAD_LEFT) {
        entity_ax[0] = -0x0040;
        entity_dir[0] = -1;
        ++entity_anim[0];
    } else if (player_pad & PAD_RIGHT) {
        entity_ax[0] = +0x0040;
        entity_dir[0] = +1;
        ++entity_anim[0];
    } else {
        entity_ax[0] = 0;
    }

    if (player_pad & PAD_A) {
        if (entity_on_ground[0] && player_jump == 0) {
            ++player_jump;
        }
        if (player_jump > 0 && player_jump < 9) {
            entity_ay[0] = -0x280;
            ++player_jump;
        }
    } else {
        if (player_jump) player_jump = 0;
    }
    return PLAYER_ALIVE;
}

void __fastcall__ entity_check_load_screen(void) {
    xx = entity_px[0] >> 8;
    yy = entity_py[0] >> 8;

    if (xx > 248 && entity_vx[0] > 0) {
        entity_px[0] = 0;
        ++player_rx;
        player_room = header.levelmap[player_ry*16+player_rx];
        entity_load_screen();
    } else if (xx < 8 && entity_vx[0] < 0) {
        entity_px[0] = 0xFF00;
        --player_rx;
        player_room = header.levelmap[player_ry*16+player_rx];
        entity_load_screen();
    }
    if (yy > 232 && entity_vy[0] > 0) {
        entity_py[0] = 16;
        ++player_ry;
        player_room = header.levelmap[player_ry*16+player_rx];
        entity_load_screen();
    } else if (yy < 16 && entity_vy[0] < 0) {
        entity_py[0] = 0xE800;
        --player_ry;
        player_room = header.levelmap[player_ry*16+player_rx];
        entity_load_screen();
    }

    return;
}

void __fastcall__ entity_set_screen(uint8_t scrn) {
    player_room = scrn;
}

void __fastcall__ entity_player_checkpoint(void) {
    player_rx = player_ckpt_rx;
    player_ry = player_ckpt_ry;
    player_room = player_ckpt_room;
    entity_set_player(player_ckpt_x, player_ckpt_y, false);
    entity_load_screen();
}

void __fastcall__ entity_load_screen(void) {
    static int i;
    ppu_off();
    oam_clear();
    entity_kill_all();
    copy_to_vram_simple(player_room);
	ppu_on_all();

    for(i=0; i<16; i+=2) {
        xx = screen[240+i];
        if (xx) {
            yy = (xx & 0x0F) << 4;
            xx &= 0xF0;
            if (!(entity_taken[player_room] & bittable[xx>>5]))
                entity_new(screen[240+i+1], xx, yy);
        }
    }
}
