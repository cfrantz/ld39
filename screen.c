#include <stdio.h>
#include <stdint.h>

#include "nesutil.h"

uint8_t objtable0[8][4] = {
    { 0, 0, 0, 0 },  // space
};

uint8_t objtable1[8][4] = {
    { 0, 0, 0, 0 },  // @
    { 0, 0, 0, 0 },  // A
    { 0, 0, 0, 0 },  // B
    { 0, 0, 0, 0 },  // C
    { 0x84, 0x85, 0x86, 0x87 },  // D
    { 0x82, 0x82, 0x82, 0x82 },  // E
    { 0x81, 0x81, 0x81, 0x81 },  // F
    { 0x80, 0x80, 0x80, 0x80 },  // G

};


uint8_t screen[16*15] =
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
//    printf("bc %d %d %02x\n", x, y, screen[y*16+x] & 0x0C);
    return screen[(uint8_t)(y*16+x)] & 0x0C;
}

