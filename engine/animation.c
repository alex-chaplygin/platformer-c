#include <stdlib.h>
#include <string.h>
#include "animation.h"
#include "backend.h"

animation_t* create_animation(image_t **frames, int frame_count, int speed, int looping) {
    if (!frames || frame_count <= 0)
        return NULL;

    animation_t *anim = malloc(sizeof(animation_t));
    if (!anim)
        return NULL;

    anim->frames = malloc(sizeof(image_t*) * frame_count);
    if (!anim->frames) {
        free(anim);
        return NULL;
    }
    memcpy(anim->frames, frames, sizeof(image_t*) * frame_count);

    anim->frame_count = frame_count;
    anim->speed = speed < 1 ? 1 : speed;
    anim->looping = looping ? 1 : 0;
    anim->current_frame = 0;
    anim->tick = 0;
    return anim;
}

void update_animation(animation_t *anim) {
    if (!anim)
        return;

    anim->tick++;
    if (anim->tick < anim->speed)
        return;

    anim->tick = 0;
    if (anim->current_frame + 1 < anim->frame_count) {
        anim->current_frame++;
    } else if (anim->looping) {
        anim->current_frame = 0;
    }
}

void draw_animation(animation_t *anim, int x, int y) {
    if (!anim)
        return;
    draw_image(anim->frames[anim->current_frame], x, y);
}


void destroy_animation(animation_t *anim) {
    if (!anim)
        return;
    free(anim->frames);
    free(anim);
}
