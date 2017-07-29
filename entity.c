#include <stdio.h>
#include <stdint.h>
#include "entity.h"
#include "screen.h"
#include "nesutil.h"

uint8_t player_pad;
uint8_t player_jump;
uint8_t spridx;

uint8_t entity_colx_x0[] = {  1, };
uint8_t entity_colx_y0[] = {  2, };
uint8_t entity_colx_x1[] = {  6, };
uint8_t entity_colx_y1[] = { 14, };

uint8_t entity_coly_x0[] = {  2, };
uint8_t entity_coly_y0[] = {  0, };
uint8_t entity_coly_x1[] = {  5, };
uint8_t entity_coly_y1[] = { 16, };

uint8_t entity_sprites[][4] = {
    { 1, 3, 1, 3 },
};

int entity_maxx[] = {
    0x180,
};

int entity_maxy[] = {
    0x500,
};

uint8_t entity_id[MAX_ENTITY];
uint16_t entity_px[MAX_ENTITY];
uint16_t entity_py[MAX_ENTITY];

int entity_ax[MAX_ENTITY];
int entity_ay[MAX_ENTITY];

int entity_vx[MAX_ENTITY];
int entity_vy[MAX_ENTITY];
uint8_t entity_on_ground[MAX_ENTITY];

int8_t entity_dir[MAX_ENTITY];
uint8_t entity_anim[MAX_ENTITY];

static uint8_t cur_id;
static uint8_t cur_index;

uint8_t __fastcall__ entity_left_collision(int delta) {
    static uint16_t px;
    static uint8_t py, xx;

    px = entity_px[cur_index] + delta;
    px += entity_colx_x0[cur_id] << 8;
    xx = px >> 8;
    py = entity_py[cur_index] >> 8;
    if (basic_collision(xx, py + entity_colx_y0[cur_id]) ||
        basic_collision(xx, py + entity_colx_y1[cur_id])) {
        return xx & 0xf0;
    }
    return 0;
}

uint8_t __fastcall__ entity_right_collision(int delta) {
    static uint16_t px;
    static uint8_t py, xx;

    px = entity_px[cur_index] + delta;
    px += entity_colx_x1[cur_id] << 8;
    xx = px >> 8;
    py = entity_py[cur_index] >> 8;
    if (basic_collision(xx, py + entity_colx_y0[cur_id]) ||
        basic_collision(xx, py + entity_colx_y1[cur_id])) {
        return xx & 0xf0;
    }
    return 0;
}

uint8_t __fastcall__ entity_top_collision(int delta) {
    static uint16_t py;
    static uint8_t px, yy;

    py = entity_py[cur_index] + delta;
    py += entity_coly_y0[cur_id] << 8;
    yy = py >> 8;
    px = entity_px[cur_index] >> 8;
    if (basic_collision(px + entity_coly_x0[cur_id], yy) ||
        basic_collision(px + entity_coly_x1[cur_id], yy)) {
        return yy & 0xf0;
    }
    return 0;
}

uint8_t __fastcall__ entity_bottom_collision(int delta) {
    static uint16_t py;
    static uint8_t px, yy;

    py = entity_py[cur_index] + delta;
    py += entity_coly_y1[cur_id] << 8;
    yy = py >> 8;
    px = entity_px[cur_index] >> 8;
    if (basic_collision(px + entity_coly_x0[cur_id], yy) ||
        basic_collision(px + entity_coly_x1[cur_id], yy)) {
        return yy & 0xf0;
    }
    return 0;
}

void __fastcall__ entity_compute_position_x(void) {
    static uint8_t c;

    if (entity_vx[cur_index] > 0) {
        c = entity_right_collision(entity_vx[cur_index]);
        if (c) {
            entity_px[cur_index] = (c - entity_colx_x1[cur_id]) << 8;
            entity_vx[cur_index] = 0;
        } else {
            entity_px[cur_index] += entity_vx[cur_index];
        }
        c = entity_left_collision(0);
        if (c) {
            entity_px[cur_index] = (c + 0x10 - entity_colx_x0[cur_id]) << 8;
        }
    } else {
        c = entity_left_collision(entity_vx[cur_index]);
        if (c) {
            entity_px[cur_index] = (c + 0x10 - entity_colx_x0[cur_id]) << 8;
            entity_vx[cur_index] = 0;
        } else {
            entity_px[cur_index] += entity_vx[cur_index];
        }
        c = entity_right_collision(0);
        if (c) {
            entity_px[cur_index] = (c - entity_colx_x1[cur_id]) << 8;
        }
    }
}

void __fastcall__ entity_compute_position_y(void) {
    static uint8_t c;

    entity_on_ground[cur_index] = 0;
    if (entity_vy[cur_index] > 0) {
        c = entity_bottom_collision(entity_vy[cur_index]);
        if (c) {
            entity_py[cur_index] = (c - entity_coly_y1[cur_id]) << 8;
            entity_vy[cur_index] = 0;
            entity_on_ground[cur_index] = 1;
        } else {
            entity_py[cur_index] += entity_vy[cur_index];
        }
        c = entity_top_collision(0);
        if (c) {
            entity_py[cur_index] = (c + 0x10 - entity_coly_y0[cur_id]) << 8;
        }
    } else {
        c = entity_top_collision(entity_vy[cur_index]);
        if (c) {
            entity_py[cur_index] = (c + 0x10 - entity_coly_y0[cur_id]) << 8;
            entity_vy[cur_index] = 0;
        } else {
            entity_py[cur_index] += entity_vy[cur_index];
        }
        c = entity_bottom_collision(0);
        if (c) {
            entity_py[cur_index] = (c - entity_coly_y1[cur_id]) << 8;
        }
    }
}


void __fastcall__ entity_compute_position(uint8_t entity) {
    static int fx;

    cur_index = entity;
    cur_id = entity_id[cur_index];
    fx = 0;
    if (entity_on_ground[cur_index])
        fx = 0x0040;

    if (entity_vx[cur_index] > 0)
        entity_vx[cur_index] -= fx;
    else if (entity_vx[cur_index] < 0)
        entity_vx[cur_index] += fx;

    entity_vx[cur_index] += entity_ax[cur_index];
    entity_vy[cur_index] += entity_ay[cur_index];

    if (entity_vx[cur_index] > entity_maxx[cur_id]) {
        entity_vx[cur_index] = entity_maxx[cur_id];
    } else if (entity_vx[cur_index] < -entity_maxx[cur_id]) {
        entity_vx[cur_index] = -entity_maxx[cur_id];
    }
    if (entity_vy[cur_index] > entity_maxy[cur_id]) {
        entity_vy[cur_index] = entity_maxy[cur_id];
    } else if (entity_vy[cur_index] < -entity_maxy[cur_id]) {
        entity_vy[cur_index] = -entity_maxy[cur_id];
    }

    entity_compute_position_x();
    entity_compute_position_y();
}

void __fastcall__ entity_newframe(void) {
    spridx = 0;
    entity_ay[0] = 0x100;
}

void __fastcall__ entity_draw(uint8_t index) {
    static uint8_t id;
    static uint8_t a, flags;
    id = entity_id[index];

    a = (entity_anim[index] / 4) & 3;
    flags = (entity_dir[index] < 0) ? 0x40 : 0;
    spridx = oam_spr(entity_px[index]>>8, entity_py[index]>>8, 
                     entity_sprites[index][a], flags, spridx);

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
    player_pad = pad_poll(0);

    if (player_pad & PAD_LEFT) {
        entity_ax[0] = -0x0080;
        entity_dir[0] = -1;
        entity_anim[0]++;
    } else if (player_pad & PAD_RIGHT) {
        entity_ax[0] = +0x0080;
        entity_dir[0] = +1;
        entity_anim[0]++;
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
