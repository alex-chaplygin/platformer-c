/**
 * @file world.c
 * @brief Реализация функций игрового мира на основе двусвязного списка.
 */

#include <stdio.h>
#include <stdlib.h>
#include "world.h"

 // Указатель на первый элемент списка (голову) и счетчик объектов
static object_t* head = NULL;
static int object_count = 0;

/**
 * @brief Добавляет новый объект в начало двусвязного списка.
 */
object_t* add_object(vec3_t pos, vec3_t v, vec3_t a) {
    // Выделяем память под новый узел в куче
    object_t* new_obj = (object_t*)malloc(sizeof(object_t));
    if (new_obj == NULL) {
        return NULL; // Ошибка выделения памяти
    }

    new_obj->pos = pos;
    new_obj->v = v;
    new_obj->a = a;

    // Вставляем узел в начало списка (head)
    new_obj->next = head;
    new_obj->prev = NULL;

    if (head != NULL) {
        head->prev = new_obj;
    }

    head = new_obj;
    object_count++;

    return new_obj;
}

/**
 * @brief Удаляет объект из двусвязного списка по его указателю.
 */
void remove_object(object_t* o) {
    if (o == NULL) return;

    // Если удаляемый объект — это голова списка
    if (o == head) {
        head = o->next;
    }

    // Перепривязываем указатель next у предыдущего элемента
    if (o->prev != NULL) {
        o->prev->next = o->next;
    }

    // Перепривязываем указатель prev у следующего элемента
    if (o->next != NULL) {
        o->next->prev = o->prev;
    }

    // Освобождаем память узла
    free(o);
    object_count--;
}

/**
 * @brief Устанавливает новую скорость для объекта.
 */
void set_velocity(object_t* o, vec3_t v) {
    if (o != NULL) {
        o->v = v;
    }
}

/**
 * @brief Устанавливает новое ускорение для объекта.
 */
void set_accel(object_t* o, vec3_t a) {
    if (o != NULL) {
        o->a = a;
    }
}

/**
 * @brief Обновляет физику всех объектов мира за один шаг (v += a, p += v).
 */
void world_update(void) {
    object_t* current = head;
    while (current != NULL) {
        current->v = vec3_add(current->v, current->a);     // v += a
        current->pos = vec3_add(current->pos, current->v); // p += v
        current = current->next;
    }
}

/**
 * @brief Выводит текущие координаты всех объектов мира в консоль.
 */
void world_print(void) {
    printf("--- Game World (objects: %d) ---\n", object_count);
    object_t* current = head;
    int i = 1;
    while (current != NULL) {
        printf("Object %d: Position (%.1f, %.1f, %.1f) | Velocity (%.1f, %.1f, %.1f)\n",
            i,
            current->pos.x, current->pos.y, current->pos.z,
            current->v.x, current->v.y, current->v.z);
        current = current->next;
        i++;
    }
    printf("----------------------------------\n\n");
}

/**
 * @brief Полностью очищает всю память двусвязного списка мира.
 */
void world_free(void) {
    object_t* current = head;
    while (current != NULL) {
        object_t* next_obj = current->next; // Сохраняем указатель на следующий узел
        free(current);                      // Освобождаем текущий
        current = next_obj;
    }
    head = NULL;
    object_count = 0;
}