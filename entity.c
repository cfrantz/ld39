#include <stdio.h>
#include <stdint.h>
#include "entity.h"
#include "screen.h"
#include "nesutil.h"

uint8_t player_pad;
uint8_t player_jump;
uint8_t spridx;

uint8_t entity_colx[][4] = {
    { 1, 2, 6, 14 },
};

uint8_t entity_coly[][4] = {
    //{ 1, 1, 6, 14 },
    { 2, 0, 5, 16 },
};

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

uint8_t entity_left_collision(uint8_t index, int delta) {
    static uint8_t id;
    static uint16_t px;
    static uint8_t py, xx;

    id = entity_id[index];
    px = entity_px[index] + delta;
    px += entity_colx[id][0] << 8;
    xx = px >> 8;
    py = entity_py[index] >> 8;
    if (basic_collision(xx, py + entity_colx[id][1]) ||
        basic_collision(xx, py + entity_colx[id][3])) {
        return xx & 0xf0;
    }
    return 0;
}

uint8_t entity_right_collision(uint8_t index, int delta) {
    static uint8_t id;
    static uint16_t px;
    static uint8_t py, xx;

    id = entity_id[index];
    px = entity_px[index] + delta;
    px += entity_colx[id][2] << 8;
    xx = px >> 8;
    py = entity_py[index] >> 8;
    if (basic_collision(xx, py + entity_colx[id][1]) ||
        basic_collision(xx, py + entity_colx[id][3])) {
        return xx & 0xf0;
    }
    return 0;
}

uint8_t entity_top_collision(uint8_t index, int delta) {
    static uint8_t id;
    static uint16_t py;
    static uint8_t px, yy;

    id = entity_id[index];
    py = entity_py[index] + delta;
    py += entity_coly[id][1] << 8;
    yy = py >> 8;
    px = entity_px[index] >> 8;
    if (basic_collision(px + entity_coly[id][0], yy) ||
        basic_collision(px + entity_coly[id][2], yy)) {
        return yy & 0xf0;
    }
    return 0;
}

uint8_t entity_bottom_collision(uint8_t index, int delta) {
    static uint8_t id;
    static uint16_t py;
    static uint8_t px, yy;

    id = entity_id[index];
    py = entity_py[index] + delta;
    py += entity_coly[id][3] << 8;
    yy = py >> 8;
    px = entity_px[index] >> 8;
    if (basic_collision(px + entity_coly[id][0], yy) ||
        basic_collision(px + entity_coly[id][2], yy)) {
        return yy & 0xf0;
    }
    return 0;
}

void entity_compute_position_x(uint8_t index) {
    static uint8_t id;
    static uint8_t c;

    id = entity_id[index];
    if (entity_vx[index] > 0) {
        c = entity_right_collision(index, entity_vx[index]);
        if (c) {
            entity_px[index] = (c - entity_colx[id][2]) << 8;
            entity_vx[index] = 0;
        } else {
            entity_px[index] += entity_vx[index];
        }
        c = entity_left_collision(index, 0);
        if (c) {
            entity_px[index] = (c + 0x10 - entity_colx[id][0]) << 8;
        }
    } else {
        c = entity_left_collision(index, entity_vx[index]);
        if (c) {
            entity_px[index] = (c + 0x10 - entity_colx[id][0]) << 8;
            entity_vx[index] = 0;
        } else {
            entity_px[index] += entity_vx[index];
        }
        c = entity_right_collision(index, 0);
        if (c) {
            entity_px[index] = (c - entity_colx[id][2]) << 8;
        }
    }
}

void entity_compute_position_y(uint8_t index) {
    static uint8_t id;
    static uint8_t c;

    id = entity_id[index];
    entity_on_ground[index] = 0;
    if (entity_vy[index] > 0) {
        c = entity_bottom_collision(index, entity_vy[index]);
        if (c) {
            entity_py[index] = (c - entity_coly[id][3]) << 8;
            entity_vy[index] = 0;
            entity_on_ground[index] = 1;
        } else {
            entity_py[index] += entity_vy[index];
        }
        c = entity_top_collision(index, 0);
        if (c) {
            entity_py[index] = (c + 0x10 - entity_coly[id][1]) << 8;
        }
    } else {
        c = entity_top_collision(index, entity_vy[index]);
        if (c) {
            entity_py[index] = (c + 0x10 - entity_coly[id][1]) << 8;
            entity_vy[index] = 0;
        } else {
            entity_py[index] += entity_vy[index];
        }
        c = entity_bottom_collision(index, 0);
        if (c) {
            entity_py[index] = (c - entity_coly[id][3]) << 8;
        }
    }
}


void entity_compute_position(uint8_t index) {
    static uint8_t id;
    static int fx;

    id = entity_id[index];
    fx = 0;
    if (entity_on_ground[index])
        fx = 0x0040;

    if (entity_vx[index] > 0)
        entity_vx[index] -= fx;
    else if (entity_vx[index] < 0)
        entity_vx[index] += fx;

    entity_vx[index] += entity_ax[index];
    entity_vy[index] += entity_ay[index];

    if (entity_vx[index] > entity_maxx[id]) {
        entity_vx[index] = entity_maxx[id];
    } else if (entity_vx[index] < -entity_maxx[id]) {
        entity_vx[index] = -entity_maxx[id];
    }
    if (entity_vy[index] > entity_maxy[id]) {
        entity_vy[index] = entity_maxy[id];
    } else if (entity_vy[index] < -entity_maxy[id]) {
        entity_vy[index] = -entity_maxy[id];
    }

    entity_compute_position_x(index);
    entity_compute_position_y(index);
}

void entity_newframe(void) {
    spridx = 0;
    entity_ay[0] = 0x100;
}

void entity_draw(uint8_t index) {
    static uint8_t id;
    static uint8_t a, flags;
    id = entity_id[index];

    a = (entity_anim[index] / 4) & 3;
    flags = (entity_dir[index] < 0) ? 0x40 : 0;
    spridx = oam_spr(entity_px[index]>>8, entity_py[index]>>8, 
                     entity_sprites[index][a], flags, spridx);

}

void entity_set_position(uint8_t index, uint8_t x, uint8_t y) {
    entity_ax[index] = 0;
    entity_ay[index] = 0;
    entity_vx[index] = 0;
    entity_vy[index] = 0;
    entity_px[index] = x<<8;
    entity_py[index] = y<<8;
    entity_on_ground[index] = 1;
}


void entity_player_control(void) {
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
