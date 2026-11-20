#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "image.h"
#include "animation.h"

typedef struct sprite_t
{
    animation_t *anim; // указатель на изображение спрайта
    int x; // координата x спрайта
    int y; // координата y спрайта             
    int z; // координата z спрайта для определения порядка отрисовки
     struct sprite_t *prev; // указатель на предыдущий спрайт в списке
     struct sprite_t *next; // указатель на следующий спрайт в списке
} sprite_t;

sprite_t *add_sprite(animation_t *anim, int x, int y, int z);
void set_tiles(int w, int h, char *file_name);
void set_screen(int **screen, int cols, int rows);
void draw_screen();
void move_sprite(sprite_t *s, int x, int y);
void remove_sprite(sprite_t *s);
void draw_sprites();

#endif
