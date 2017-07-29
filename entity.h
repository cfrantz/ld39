#ifndef LD39_ENTITY_H
#define LD39_ENTITY_H

#define MAX_ENTITY 16
void entity_newframe(void);
void entity_compute_position(uint8_t index);
void entity_draw(uint8_t index);
void entity_player_control(void);
void entity_set_position(uint8_t index, uint8_t x, uint8_t y);

#endif // LD39_ENTITY_H
