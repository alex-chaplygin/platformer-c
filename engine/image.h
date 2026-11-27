#ifndef IMAGE_H
#define IMAGE_H
 
typedef struct 
{
    int width;
    int height;
    void *data;
} image_t;

image_t* make_image(int w, int h, void *data);
int image_width(image_t *i);
int image_height(image_t *i);
void *image_data(image_t *i);

#endif