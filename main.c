#include <stdio.h>
#include "backend.h"
#include "graphics.h"
#include "animation.h"
int main(int argc, char *argv[]) {
    create_window(800, 600);
    set_fps(60);
    set_tiles(32, 32, "images/atlas.png");
    int screen_cols = 25;
    int screen_rows = 19;
    int map[screen_rows][screen_cols]; // двумерный массив для карты
    int *screen[screen_rows]; // массив указателей на строки карты
    for (int row = 0; row < screen_rows; row++) {
        screen[row] = map[row];
        for (int col = 0; col < screen_cols; col++)
            map[row][col] = (row + col) % 2;
    }
    image_t* s1 = load_image("images/s1.png"); 
    image_t* s2 = load_image("images/s2.png"); 
    image_t* s3 = load_image("images/s3.png");
    image_t* s4 = load_image("images/s4.png");
    animation_t* anim = create_animation((image_t*[]){s1, s2}, 2, 10, 1);
    sprite_t* spr3 = add_sprite(s3, -100, 200, 1);
    sprite_t* spr4 = add_sprite(s4, 850, 200, 0);
    set_screen(screen, screen_cols, screen_rows);
    int move_x1 = 3; // скорость движения спрайта 1
    int move_x2 = -3; // скорость движения спрайта 2
    while (!is_quit()) {
        // Изменение настроек fps
        if (key_pressed("1")) set_fps(10);
        if (key_pressed("2")) set_fps(60);
        if (key_pressed("3")) set_fps(144);

        move_sprite(spr3, spr3->x + move_x1, spr3->y);
        move_sprite(spr4, spr4->x + move_x2, spr4->y);
        if (spr3->x > 800)
            move_sprite(spr3, -100, spr3->y);
        if (spr4->x < -100)
            move_sprite(spr4, 850, spr4->y);  
        draw_screen();
        draw_sprites();
        draw_animation(anim, 100, 50);
        update_window();
        update_animation(anim);
    }
    destroy_window();
    return 0;
}