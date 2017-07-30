#ifndef LD39_LEVELS_H
#define LD39_LEVELS_H
#include <stdint.h>

struct LevelHeader {
    uint8_t name[16];
    uint8_t levelmap[256];
    // Starting room number
    uint8_t start_room;
    // Starting location in the levelmap
    uint8_t start_rx, start_ry;
    // Starting pixel x, y
    uint8_t start_px, start_py;
};

extern struct LevelHeader header;

extern const uint8_t level0[][16*16];
extern const struct LevelHeader header0;

#endif // LD39_LEVELS_H
