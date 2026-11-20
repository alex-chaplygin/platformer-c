#include "image.h"
#include <stdlib.h>

/**
 * @brief Создает изображение с заданной шириной, высотой и данными.
 * @param w Ширина изображения.
 * @param h Высота изображения.
 * @param data Указатель на данные изображения.
 * @return Указатель на созданное изображение.
 */
image_t* make_image(int w, int h, void *data)
{
    image_t *img = malloc(sizeof(image_t));
    img->width = w;
    img->height = h;
    img->data = data;
    return img;
}

/**
 * @brief Получает ширину изображения.
 * @param i Указатель на изображение.
 * @return Ширина изображения.
 */
int image_width(image_t *i)
{
    return i->width;
}

/**
 * @brief Получает высоту изображения.
 * @param i Указатель на изображение.
 * @return Высота изображения.
 */
int image_height(image_t *i)
{
    return i->height;
}

/**
 * @brief Получает указатель на данные изображения.
 * @param i Указатель на изображение.
 * @return Указатель на данные изображения.
 */
void *image_data(image_t *i)
{
    return i->data;
}