#ifndef LD39_ENTITY_H
#define LD39_ENTITY_H

#define MAX_ENTITY 16
void __fastcall__ entity_newframe(void);
void __fastcall__ entity_compute_position(uint8_t index);
void __fastcall__ entity_draw(uint8_t index);
void __fastcall__ entity_player_control(void);
void __fastcall__ entity_set_player(uint8_t x, uint8_t y);

void __fastcall__ entity_new(uint8_t id, uint8_t x, uint8_t y);
void __fastcall__ entity_update(void);
void __fastcall__ entity_update_all(void);

void __fastcall__ entity_draw_all(void);
void __fastcall__ entity_draw_stats(void);

void __fastcall__ entity_set_screen(uint8_t scrn);
void __fastcall__ entity_check_load_screen(void);
void __fastcall__ entity_load_screen(void);

extern uint8_t player_keys;

#endif // LD39_ENTITY_H
