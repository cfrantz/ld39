#include <stdio.h>
#include <stdint.h>
#include "entity.h"
#include "screen.h"
#include "nesutil.h"

//////////////////////////////////////////////////////////////////////
// The following are parameters indexed on entity id
// 0: player
// 1: enemy type 1
// 2: enemy type 2 (etc)
//////////////////////////////////////////////////////////////////////
uint8_t entity_colx_x0[] = {  1, };
uint8_t entity_colx_y0[] = {  2, };
uint8_t entity_colx_x1[] = {  6, };
uint8_t entity_colx_y1[] = { 14, };

uint8_t entity_coly_x0[] = {  2, };
uint8_t entity_coly_y0[] = {  0, };
uint8_t entity_coly_x1[] = {  5, };
uint8_t entity_coly_y1[] = { 16, };

int entity_maxx[] = {
    0x180,
};

int entity_maxy[] = {
    0x500,
};

uint8_t entity_sprites[][4] = {
    { 1, 3, 1, 3 },
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
uint8_t player_pad;
uint8_t player_jump;
uint8_t spridx;

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

    if (!(player_pad & (PAD_LEFT | PAD_RIGHT))) {
        if (vx > 0)
            vx -= fx;
        else if (vx < 0)
            vx += fx;
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
    entity_ay[0] = 0x100;
}

void __fastcall__ entity_draw(uint8_t index) {
    static uint8_t id;
    id = entity_id[index];
    spridx = oam_spr(entity_px[index]>>8, entity_py[index]>>8, 
                     entity_sprite_id[index],
                     entity_sprite_attr[index], spridx);

}

void __fastcall__ entity_set_position(uint8_t index, uint8_t x, uint8_t y) {
    entity_ax[index] = 0;
    entity_ay[index] = 0;
    entity_vx[index] = 0;
    entity_vy[index] = 0;
    entity_px[index] = x<<8;
    entity_py[index] = y<<8;
    entity_on_ground[index] = 1;
}


void __fastcall__ entity_player_control(void) {
    static uint8_t on_ladder, a;
    player_pad = pad_poll(0);

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
}
