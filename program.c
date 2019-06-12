#ifndef LARTICLES_H_INCLUDED
#include "larticles.c"
#endif
#ifndef VISUAL_H_INCLUDED
#include "visual.c"
#endif
void Larticles_Blits(SDL_Renderer *renderer, Larticles *larticles, float scale, float x, float y);

void Larticles_Blits(SDL_Renderer *renderer, Larticles *larticles, float scale, float x, float y)
{
	for (int i=0; i<larticles->larticles_amount +1; i++)
	{
		Draw_circle(renderer, (int)((larticles->larticles[i].x+x) * scale),(int)((larticles->larticles[i].y+y) * scale),
		(int)((larticles->larticles[i].r +1) * scale), (int)(larticles->larticles[i].color[0]),
		(int)(larticles->larticles[i].color[1]),
		(int)(larticles->larticles[i].color[2]), (int)(larticles->larticles[i].color[3]), 1);

		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderDrawLine(renderer, (int)((larticles->larticles[i].x+x) * scale), (int)((larticles->larticles[i].y+y) * scale),
		(int)(((larticles->larticles[i].x+x) + larticles->larticles[i].r * cos(larticles->larticles[i].angle)) * scale),
		(int)(((larticles->larticles[i].y+y) + larticles->larticles[i].r * sin(larticles->larticles[i].angle)) * scale)
		);
	}
}

int main( int argc, char* args[] )
{

	clock_t rstart, rstop;
	rstart = clock();

	SDL_Window *window;
	SDL_Renderer *renderer;
	Larticles larticles;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Arys",0,0,SCREEN_X,SCREEN_Y,0);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	rstop = clock();
	int rtime = rstop - rstart;
	int seed = time(NULL);
	srand(seed);
	int delay = 0;
	int fullscreen = 0;



	Larticles_Initiate(&larticles);

	float scale = (float)SCREEN_Y/((float)UNIVERSE_SIZE);
	float beginscale = (float)SCREEN_Y/((float)UNIVERSE_SIZE);
	float x = ((float)UNIVERSE_SIZE/2.0f - SCREEN_X/2);
	float y = 0.0f;
	float dt = 1000.0f;

	int running = 1;
	int doe = 1;

	while(running==1)
	{
		clock_t start, stop;
		start = clock();


		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					//running = 0;
					break;
				case SDL_MOUSEWHEEL:

					scale += event.wheel.y*0.1;
					printf("%f\n",scale);
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = 0;
							break;
						case SDLK_RIGHT:
							x -= 20.0f;
							break;
						case SDLK_d:
							x -= 20.0f;
							break;
						case SDLK_LEFT:
							x += 20.0f;
							break;
						case SDLK_q:
							x += 20.0f;
							break;
						case SDLK_UP:
							y += 20.0f;
							break;
						case SDLK_z:
							y += 20.0f;
							break;
						case SDLK_DOWN:
							y -= 20.0f;
							break;
						case SDLK_s:
							y -= 20.0f;
							break;
						case SDLK_r:
							x = ((float)UNIVERSE_SIZE/2.0f - SCREEN_X/2);
							y = 0.0f;
							scale = beginscale;
							break;
						case SDLK_i:
							delay += 1;
							break;
						case SDLK_j:
							if (delay > 0)
							{
								delay -= 1;
							}
							break;
                        			case SDLK_1:
							if (doe == 0)
							{
								doe = 1;
							}
							else
							    {
								doe = 0;
							    }
							break;
						case SDLK_f:
						if (fullscreen == 0)
							//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
							fullscreen = 1;
						else
						{
							fullscreen = 0;
						}
						case SDLK_x:
							Larticles_Doe(&larticles);

					}

			}




		}
		if (doe==1)
		{
		    Larticles_Doe(&larticles);
		}
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		Larticles_Blits(renderer,&larticles,scale,x,y);
		SDL_RenderPresent(renderer);
		SDL_Delay(delay);
		stop = clock();
		dt = (float)(stop - start);
   		printf("dt = %f\n amount = %d\n", dt,larticles.larticles_amount);
	}



	SDL_DestroyWindow(window);

	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return 0;
}
