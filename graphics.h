#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "animation.h"

enum {
    /// Одиночное изображение
    SPRITE,
    /// Анимация
    ANIMATION
};

typedef struct sprite_t
{
    int type; // тип спрайта
    union {
	image_t *im; // указатель на изображение спрайта
	animation_t *anim; // указатель на анимацию
    };
    int x; // координата x спрайта
    int y; // координата y спрайта             
    int z; // координата z спрайта для определения порядка отрисовки
    struct sprite_t *prev; // указатель на предыдущий спрайт в списке
    struct sprite_t *next; // указатель на следующий спрайт в списке
} sprite_t;

sprite_t *add_sprite(image_t *im, int x, int y, int z);
sprite_t *add_animation(animation_t *a, int x, int y, int z);
void set_tiles(int w, int h, char *file_name);
void set_screen(int **screen, int cols, int rows);
void draw_screen();
void move_sprite(sprite_t *s, int x, int y);
void remove_sprite(sprite_t *s);
void draw_sprites();

#endif
