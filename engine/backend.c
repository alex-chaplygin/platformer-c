#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "backend.h"

static SDL_Window   *window   = NULL; // указатель на окно
static SDL_Renderer *renderer = NULL; // указатель на рендерер
static Uint32 frame_delay = 1000 / 60; // задержка в миллисекундах для обновления окна 
static Uint32 last_frame_time = 0; // ремя с начала последнего кадра
static int quit_flag = 0; // флаг выхода из программы

/**
 * @brief Создает окно с заданной шириной и высотой.
 * @param width Значение ширины окна.
 * @param height Значение высоты окна.
 */
void create_window(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Ошибка создания окна: %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Ошибка создания рендерера: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }
    last_frame_time = SDL_GetTicks();
}
 
/**
 * @brief Уничтожает окно и освобождает ресурсы.
 */
void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 * @brief Задаёт fps игры.
 * @param fps Fps, который задаёт пользователь.
 */
void set_fps(int fps) {
    if (fps <= 0) 
        fps = 60;
    frame_delay = 1000 / fps;
}

/**
 * @brief Загружает изображение из файла.
 * @param path Путь к файлу изображения.
 * @return Загруженное изображение в виде структуры image_t, или NULL в случае ошибки.
 */
image_t* load_image(char *path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (!texture) {
        printf("Ошибка загрузки изображения: %s\n", SDL_GetError());
        return NULL;
    }
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return make_image(w, h, (void*)texture);
}

/**
 * @brief Рисует изображение на окне в заданных координатах.
 * @param im Изображение для рисования.
 * @param x Координата X для размещения изображения.
 * @param y Координата Y для размещения изображения.
 */
void draw_image(image_t *im, int x, int y) {
    SDL_Rect place = {x, y, im->width, im->height};
    SDL_RenderCopy(renderer, (SDL_Texture*)im->data, NULL, &place);
}

/**
 * @brief Рисует часть изображения на окне в заданных координатах.
 * @param im Изображение для рисования.
 * @param part_x Координата X верхнего левого угла части изображения.
 * @param part_y Координата Y верхнего левого угла части изображения.
 * @param part_w Ширина части изображения.
 * @param part_h Высота части изображения.
 * @param x Координата X для размещения изображения.
 * @param y Координата Y для размещения изображения.
 */
void draw_part_image(image_t *im, int part_x, int part_y, int part_w, int part_h, int x, int y) {
    SDL_Rect part = {part_x, part_y, part_w, part_h};
    SDL_Rect place = {x, y, part_w, part_h};
    SDL_RenderCopy(renderer, (SDL_Texture*)im->data, &part, &place);
}

/**
 * @brief Проверяет, была ли нажата клавиша.
 * @param key Символ нажатой клавиши для проверки.
 * @return 1, если клавиша нажата, иначе 0.
 */
int key_pressed(const char *key) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Scancode scancode = SDL_GetScancodeFromName(key);
    return state[scancode];
}

/**
 * @brief Проверяет, был ли запрос на выход из программы.
 * @return 1, если был запрос на выход, иначе 0.
 */
int is_quit() {
    return quit_flag;
}

/**
 * @brief Обновляет окно, обрабатывает события и отображает содержимое.
 */
void update_window() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            quit_flag = 1;
    }

    SDL_RenderPresent(renderer);

    if (frame_delay > 0) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed = current_time - last_frame_time;
        if (elapsed < frame_delay) {
            SDL_Delay(frame_delay - elapsed);
        }
    }
    last_frame_time = SDL_GetTicks();
}
