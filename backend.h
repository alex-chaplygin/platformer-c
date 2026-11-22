#ifndef BACKEND_H
#define BACKEND_H

#include "image.h"

void create_window(int width, int height);
void destroy_window();
void set_fps(int fps);
image_t* load_image(char *path);
void draw_image(image_t *im, int x, int y);
void draw_part_image(image_t *im, int part_x, int part_y, int part_w, int part_h, int x, int y);
int key_pressed(const char *key);
int is_quit();
void update_window();

#endif