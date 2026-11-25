#include <stdio.h>
#include "backend.h"
#include "graphics.h"
#include "animation.h"
#include "generator.h"
#define TILE_SIZE 32 

/**
 * @brief Проверяет имеется ли в указанном расположении героя внутри спрайта стена
 * @param map указатель на массив карты
 * @param cols количество колонок
 * @param rows количество столбцов
 * @param x координата спрайта
 * @param y координата спрайта
 * @param w ширина спрайта
 * @param h высота спрайта
 * @return int 1 если в указанном месте стена, 0 если свободно
 */
int is_wall_under_sprite(int **map, int cols, int rows, int x, int y, int w, int h) {
    int left   = x / TILE_SIZE;
    int right  = (x + w - 1) / TILE_SIZE;
    int top    = y / TILE_SIZE;
    int bottom = (y + h - 1) / TILE_SIZE;
    for (int r = top; r <= bottom; r++) {
        for (int c = left; c <= right; c++) {
            if (r < 0 || r >= rows || c < 0 || c >= cols)
                return 1;
            if (map[r][c] == 1)
                return 1; 
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    create_window(800, 600);
    set_tiles(TILE_SIZE, TILE_SIZE, "images/atlas.png");
    int screen_cols = 25;
    int screen_rows = 19;
    int map[screen_rows][screen_cols]; // двумерный массив для карты
    int *screen[screen_rows]; // массив указателей на строки карты
    for (int row = 0; row < screen_rows; row++) {
        screen[row] = map[row];
    }
   image_t* hero = load_image("images/Sprite.png");
    int hero_w = image_width(hero);
    int hero_h = image_height(hero);
    sprite_t* hero_sprite = add_sprite(hero, 100, 100, 1);
    map_fill_tiles(screen, screen_cols, screen_rows, 0, 0, screen_cols, screen_rows, 0);
    map_fill_tiles(screen, screen_cols, screen_rows, 0, 0, screen_cols, 1, 1);
    map_fill_tiles(screen, screen_cols, screen_rows, 0, screen_rows - 1, screen_cols, 1, 1);
    map_fill_tiles(screen, screen_cols, screen_rows, 0, 0, 1, screen_rows, 1);
    map_fill_tiles(screen, screen_cols, screen_rows, screen_cols - 1, 0, 1, screen_rows, 1);
    map_fill_tiles(screen, screen_cols, screen_rows, 9, 14, 7, 1, 1);
    set_screen(screen, screen_cols, screen_rows);
    int speed = 5; // скорость перемещения влево вправо
    int up_speed = 10; // скорость прыжка наверх
    int down_speed = 10; // скорость падения
    int jump_timer = 0; // время прыжка
    while (!is_quit()) {
        int new_x = hero_sprite->x;
        int new_y = hero_sprite->y;
        int on_ground = is_wall_under_sprite(screen, screen_cols, screen_rows, new_x, new_y + 1, hero_w, hero_h);
        if (key_pressed("A")) {
            if (!is_wall_under_sprite(screen, screen_cols, screen_rows, new_x - speed, new_y, hero_w, hero_h))
                new_x -= speed;
        }
        if (key_pressed("D")) {
            if (!is_wall_under_sprite(screen, screen_cols, screen_rows, new_x + speed, new_y, hero_w, hero_h))
                new_x += speed;
        }
        if ((key_pressed("W")) && on_ground) {
            jump_timer = 20;
        }
        if (jump_timer > 0) {
            if (!is_wall_under_sprite(screen, screen_cols, screen_rows, new_x, new_y - up_speed, hero_w, hero_h)) {
                new_y -= up_speed;
                jump_timer--;
            } else {
                jump_timer = 0;
            }
        } else {
            if (!is_wall_under_sprite(screen, screen_cols, screen_rows, new_x, new_y + down_speed, hero_w, hero_h)) {
                new_y += down_speed;
            } else {
                while (!is_wall_under_sprite(screen, screen_cols, screen_rows, new_x, new_y + 1, hero_w, hero_h)) {
                    new_y += 1;
                }
            }
        }
        move_sprite(hero_sprite, new_x, new_y);
        draw_screen();
        draw_sprites();
        update_window();
    }
    destroy_window();
    return 0;
}