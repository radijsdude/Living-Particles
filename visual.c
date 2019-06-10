#include "visual.h"


void Draw_rect(SDL_Renderer *renderer, int x, int y, int b, int l, int color[4], int filled)
{
	if (0 <= x && x <= SCREEN_X && 0 <= y && y <= SCREEN_Y)
	{
		SDL_SetRenderDrawColor(renderer,color[0],color[1],color[2],color[3]);
		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.w = b;
		r.h = l;
		SDL_RenderDrawRect(renderer, &r);
		SDL_RenderFillRect(renderer, &r);
	}
}

void Draw_circle(SDL_Renderer *renderer, int x, int y, int r, int color_r, int color_g, int color_b, int color_a, int filled)
{
	if (0 <= x && x <= SCREEN_X && 0 <= y && y <= SCREEN_Y)
	{
		SDL_SetRenderDrawColor(renderer,color_r,color_g,color_b,color_a);
		if (r < 2){r = 2;}
		for (int i = -r; i < r; i++)
		{
			for (int j = 0; j*j<r*r-i*i;j++)
			{
				SDL_RenderDrawPoint(renderer,x + i, y + j);
				SDL_RenderDrawPoint(renderer,x + i, y - j);
			}
		}
	}
}
