/**
 * @file vec3.c
 * @brief Реализация функций для работы с трехкомпонентными векторами.
 */
#include "vec3.h"

 /**
  * @brief Функция создания вектора.
  * Заполняет структуру переданными значениями координат x, y, z.
  */
vec3_t vec3_create(float x, float y, float z) {
	vec3_t v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

/**
 * @brief Функция сложения векторов.
 * Складывает соответствующие компоненты двух векторов (v1 и v2).
 */
vec3_t vec3_add(vec3_t v1, vec3_t v2) {
	vec3_t result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

/**
 * @brief Функция умножения вектора на скаляр.
 * Умножает каждую компоненту вектора v на заданное число scalar.
 */
vec3_t vec3_scalar(vec3_t v, float scalar) {
	vec3_t result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

/**
 * @brief Функция разности векторов.
 * Вычитает из компонентов первого вектора (v1) компоненты второго вектора (v2).
 */
vec3_t vec3_subtract(vec3_t v1, vec3_t v2) {
	vec3_t result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

