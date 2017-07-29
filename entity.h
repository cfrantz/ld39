#ifndef LD39_ENTITY_H
#define LD39_ENTITY_H

#define MAX_ENTITY 16
void __fastcall__ entity_newframe(void);
void __fastcall__ entity_compute_position(uint8_t index);
void __fastcall__ entity_draw(uint8_t index);
void __fastcall__ entity_player_control(void);
void __fastcall__ entity_set_position(uint8_t index, uint8_t x, uint8_t y);

#endif // LD39_ENTITY_H
