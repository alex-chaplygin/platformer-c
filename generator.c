/**
 * @brief Заполняет область карты указанным тайлом
 * @param map Указатель на карту
 * @param width Ширина карты
 * @param height Высота карты
 * @param x Координата X начала области
 * @param y Координата Y начала области
 * @param fill_width Ширина области
 * @param fill_height Высота области
 * @param tile Тайл для заполнения
 */
void map_fill_tiles(int **map, int width, int height, int x, int y, int fill_width, int fill_height, int tile) {
    for (int row = y; row < y + fill_height; row++) {
        for (int col = x; col < x + fill_width; col++) {
            if (row >= 0 && row < height && col >= 0 && col < width) {
                map[row][col] = tile;
            }
        }
    }
}