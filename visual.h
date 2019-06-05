
#ifndef VISUAL_H_INCLUDED
#define VISUAL_H_INCLUDED

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include "constants.h"


void Draw_circle(SDL_Renderer *renderer, int x, int y, int r, int color_r, int color_g, int color_b, int color_a, int filled);
void Draw_rect(SDL_Renderer *renderer, int x, int y, int b, int l, int color[4], int filled);
#endif
