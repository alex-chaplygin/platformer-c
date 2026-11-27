/**
 * @file world.h
 * @brief Заголовочный файл физического мира (двусвязный список).
 */

#ifndef WORLD_H
#define WORLD_H

#include "vec3.h"

 /**
  * @brief Структура физического объекта (узел двусвязного списка).
  */
typedef struct object_t {
    vec3_t pos;             // Позиция объекта в пространстве
    vec3_t v;               // Вектор скорости (velocity)
    vec3_t a;               // Вектор ускорения (accel)
    struct object_t* next;  // Указатель на следующий объект
    struct object_t* prev;  // Указатель на предыдущий объект
} object_t;

/**
 * @brief Добавляет новый объект в игровой мир.
 * @return Указатель на созданный объект object_t*
 */
object_t* add_object(vec3_t pos, vec3_t v, vec3_t a);

/**
 * @brief Удаляет объект из мира по его указателю (освобождает память узла).
 */
void remove_object(object_t* o);

/**
 * @brief Устанавливает новую скорость для объекта.
 */
void set_velocity(object_t* o, vec3_t v);

/**
 * @brief Устанавливает новое ускорение для объекта.
 */
void set_accel(object_t* o, vec3_t a);

/**
 * @brief Обновляет физику всех объектов мира (v += a, p += v).
 */
void world_update(void);

/**
 * @brief Выводит текущее состояние и координаты всех объектов мира.
 */
void world_print(void);

/**
 * @brief Полностью очищает всю память игрового мира.
 */
void world_free(void);

#endif // !WORLD_H
