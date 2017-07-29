#ifndef LD39_SCREEN_H
#define LD39_SCREEN_H

extern uint8_t screen[16*15];
void copy_to_vram_simple();
uint8_t __fastcall__ basic_collision(uint8_t x, uint8_t y);


#endif // LD39_SCREEN_H
