#include <stdio.h>
#include <stdint.h>

#include "nesutil.h"

uint8_t objtable0[16][4] = {
    { 0, 0, 0, 0 },  // space
};

uint8_t objtable1[16][4] = {
    { 0x83, 0x83, 0x83, 0x83 },  // @
    { 0x8a, 0x8a, 0x8b, 0x8b },  // A
    { 0, 0, 0, 0 },  // B
    { 0, 0, 0, 0 },  // C
    { 0x84, 0x85, 0x86, 0x87 },  // D
    { 0x82, 0x82, 0x82, 0x82 },  // E
    { 0x81, 0x81, 0x81, 0x81 },  // F
    { 0x80, 0x80, 0x80, 0x80 },  // G

    { 0, 0, 0, 0 },  // H
    { 0x81, 0x88, 0x81, 0x88 },  // I
    { 0, 0, 0, 0 },  // J
    { 0, 0, 0, 0 },  // K

    { 0, 0, 0, 0 },  // L
    { 0, 0, 0, 0 },  // M
    { 0, 0, 0, 0 },  // N
    { 0, 0, 0, 0 },  // O
};


uint8_t screen0[16*15] =
"                "
"                "
"                "
"                "
"                "
"    EEE       E "
"              E "
"      EEEE   EE "
"                "
"            D   "
"           DD   "
"gggggggggggggggg"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF";

uint8_t screen[16*15] =
"                "
"                "
"    EEE       E "
"              E "
"      EEEE   EE "
"                "
"            D   "
"           DD   "
"ggggggggggAggggg"
"FIIIIIIIIIAIIIIF"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"FFFFFFFFFFFFFFFF";

void copy_to_vram_simple() {
    static uint8_t x, y, i, a, t;

    vram_put_addr(0x2000);
    for(y=0; y<15; y++) {
        for(i=0; i<2; i++) {
            for(x=0; x<16; x++) {
                a = screen[y*16+x];
                t = (a & 0x60) >> 5;
                a &= 15;
                switch(t) {
                    case 1:
                        vram_put_data(objtable0[a][i + 0]);
                        vram_put_data(objtable0[a][i + 2]);
                        break;
                    case 2:
                        vram_put_data(objtable1[a][i + 0]);
                        vram_put_data(objtable1[a][i + 2]);
                        break;
                    case 3:
                        vram_put_data(objtable1[a][i + 0]);
                        vram_put_data(objtable1[a][i + 2]);
                        break;
                    default:
                        vram_put_data(0);
                        vram_put_data(0);

                }
            }
        }
    }

    vram_put_addr(0x23c0);
    for(y=0; y<15; y+=2) {
        for(x=0; x<16; x+=2) {
            a = ((screen[(y+0)*16+(x+0)] & 0x60) >> 5) |
                ((screen[(y+0)*16+(x+1)] & 0x60) >> 3) |
                ((screen[(y+1)*16+(x+0)] & 0x60) >> 1) |
                ((screen[(y+1)*16+(x+1)] & 0x60) << 1);
            vram_put_data(a);
            printf("%02x ", a);
        }
        printf("\n");
    }
}

uint8_t __fastcall__ basic_collision(uint8_t x, uint8_t y) {
    x = x/16;
    y = y/16;
    return screen[(uint8_t)(y*16+x)] & 0x0C;
}

uint8_t __fastcall__ screen_tile(uint8_t x, uint8_t y) {
    x = x/16;
    y = y/16;
    return screen[(uint8_t)(y*16+x)] & 0x0F;
}

