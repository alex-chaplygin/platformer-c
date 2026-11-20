#ifndef ANIMATION_H
#define ANIMATION_H

#include "image.h"

struct animation {
    image_t **frames;   
    int frame_count;    
    int speed;          
    int looping;        
    int current_frame;  
    int tick;           
};

typedef struct animation animation_t;

animation_t* create_animation(image_t **frames, int frame_count, int speed, int looping);
void update_animation(animation_t *anim);
void draw_animation(animation_t *anim, int x, int y);
void destroy_animation(animation_t *anim);

#endif
