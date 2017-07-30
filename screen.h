#ifndef LD39_SCREEN_H
#define LD39_SCREEN_H

void copy_to_vram_simple(int n);
uint8_t __fastcall__ basic_collision(uint8_t x, uint8_t y);
uint8_t __fastcall__ screen_tile(uint8_t x, uint8_t y);
extern uint8_t screen[16*16];


#endif // LD39_SCREEN_H
