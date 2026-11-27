/**
 * @file vec3.h
 * @brief Заголовочный файл для работы с трехкомпонентным вектором (float).
 */
#ifndef VEC3_H
#define VEC3_H
typedef struct {
	float x;// Координата вектора по оси X
	float y;// Координата вектора по оси Y 
	float z;// Координата вектора по оси Z 
} vec3_t;

/**
 * @brief Создание нового трехкомпонентного вектора по трем координатам.
 * @param x Координата X
 * @param y Координата Y
 * @param z Координата Z
 * @return Готовый вектор типа vec3_t
 */
vec3_t vec3_create(float x, float y, float z);

/**
 * @brief Сложение двух векторов.
 * @param v1 Первый вектор
 * @param v2 Второй вектор
 * @return Результирующий 3-й вектор (сумма v1 + v2)
 */
vec3_t vec3_add(vec3_t v1, vec3_t v2);

/**
 * @brief Умножение вектора на скаляр.
 * @param v Исходный вектор (1-й параметр)
 * @param scalar Число-скаляр (2-й параметр)
 * @return Новый вектор, полученный умножением v на scalar
 */
vec3_t vec3_scalar(vec3_t v, float scalar);

/**
 * @brief Разность двух векторов.
 * @param v1 Уменьшаемый вектор
 * @param v2 Вычитаемый вектор
 * @return Результирующий вектор (разность v1 - v2)
 */
vec3_t vec3_subtract(vec3_t v1, vec3_t v2);
#endif // !VEC3_H
