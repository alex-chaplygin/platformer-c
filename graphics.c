#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "backend.h"

image_t *atlas = NULL; //указдатель на атлас тайлов
int tile_width = 0; // ширина тайла
int tile_height = 0; // высота тайла
int tiles_in_row = 0; // количество тайлов в строке
int **screen_map = NULL; // указатель на матрицу значений карты
sprite_t *first_sprite = NULL; // указатель на первый спрайт в списке
int screen_cols = 0; // количество столбцов в экране
int screen_rows = 0; // количество строк в экране

/**
 * @brief Проверяет, является ли число степенью двойки.
 * @param n Число для проверки.
 * @return 1, если число является степенью двойки, иначе 0.
 */
int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

/**
 * @brief Устанавливает размеры тайлов и загружает атлас.
 * @param w Ширина тайла.
 * @param h Высота тайла.
 * @param file_name Путь к файлу атласа.
 */
void set_tiles(int w, int h, char *file_name){
    if (!is_power_of_two(w) || !is_power_of_two(h)) {
        printf("Ошибка: ширина и высота тайлов должны быть степенями двойки\n");
        return;
    }
    tile_width = w;
    tile_height = h;
    atlas = load_image(file_name);
    if (!atlas) {
        printf("Ошибка: не удалось загрузить атлас\n");
        return;
    }
    tiles_in_row = image_width(atlas) / tile_width;
}

/**
 * @brief Устанавливает текущий экран для отрисовки.
 * @param screen Двумерный массив, представляющий текущий экран.
 * @param cols Количество столбцов в экране.
 * @param rows Количество строк в экране.
 */
void set_screen(int **screen, int cols, int rows) {
    screen_map = screen;
    screen_cols = cols;
    screen_rows = rows;
}

/**
 * @brief Отрисовывает текущий экран, используя атлас и размеры тайлов.
 */
void draw_screen() {
    if (!atlas || !screen_map)
        return;
    for (int row = 0; row < screen_rows; row++) {
        for (int col = 0; col < screen_cols; col++) {
            int tile = screen_map[row][col];
            int part_x = (tile % tiles_in_row) * tile_width;
            int part_y = (tile / tiles_in_row) * tile_height;
            draw_part_image(atlas, part_x, part_y, tile_width, tile_height, col * tile_width, row * tile_height);
        }
    }
}

/**
 * @brief Cоздает и добавляет спрайт в список спрайтов, 
 * упорядоченный по координате z.
 * @param im Указатель на изображение спрайта.
 * @param x Координата x спрайта.
 * @param y Координата y спрайта.
 * @param z Координата z спрайта для определения порядка отрисовки).
 * @return Указатель на добавленный спрайт.
 */
sprite_t *add_sprite(image_t *im, int x, int y, int z) {
    sprite_t *s = malloc(sizeof(sprite_t));
    s->im = im;
    s->x = x;
    s->y = y;
    s->z = z;
    sprite_t *before = NULL;          
    sprite_t *after = first_sprite;   
    while (after && after->z <= z) {
        before = after;
        after = after->next;
    }
    s->prev = before;
    s->next = after;
    if (before)
        before->next = s;
    else
        first_sprite = s;       
    if (after)
        after->prev = s;
    return s;
}

/**
 * @brief Перемещает спрайт на новые координаты.
 * @param s Указатель на спрайт.
 * @param x Новая координата x спрайта.
 * @param y Новая координата y спрайта.
 */
void move_sprite(sprite_t *s, int x, int y) {
    if (!s)
        return;
    s->x = x;
    s->y = y;
}

/**
 * @brief Удаляет спрайт из списка спрайтов и освобождает его память.
 * @param s Указатель на спрайт для удаления.
 */
void remove_sprite(sprite_t *s) {
    if (!s)
        return;
    if (s->prev)
        s->prev->next = s->next;
    else
        first_sprite = s->next;     
    if (s->next) 
        s->next->prev = s->prev;
    free(s);
}

/**
 * @brief Отрисовывает все спрайты в списке спрайтов.
 */
void draw_sprites() {
    for (sprite_t *s = first_sprite; s; s = s->next)
        draw_image(s->im, s->x, s->y);
}