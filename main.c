#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "mattpaint");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect r;
	r.w = 3;
	r.h = 3;

	SDL_Point p[1024];
	int top = -1;

	int x,y;

	Uint8 *keystate;

	bool running = true;
	bool clear = false;
	bool eraser = true;
    while (running)
	{
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // canvas
		if(clear)
		{
			SDL_RenderClear(renderer);
			clear = false;
		}

		if(SDL_PollEvent(&event) )
		{
			if(event.type == SDL_QUIT)
				running = false;

			// clear canvas
			if(keystate[SDL_SCANCODE_BACKSPACE])
				clear = true;

			// eraser
			if(keystate[SDL_SCANCODE_E])
				eraser = eraser ? false : true;

			// brush size
			// ==========

			// reset
			if(keystate[SDL_SCANCODE_0])
			{
				r.w = 3;
				r.h = 3;
			}

			// increase
			if(r.w < 50 && keystate[SDL_SCANCODE_EQUALS])
			{
				r.w++;
				r.h++;
			}

			// decrease
			if(r.w > 3 && keystate[SDL_SCANCODE_MINUS])
			{
				r.w--;
				r.h--;
			}
		}

		keystate = SDL_GetKeyboardState(NULL);
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		if(eraser)
    		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		else
    		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		if(top < 1024 && SDL_BUTTON(SDL_BUTTON_LEFT) && SDL_GetMouseState(&x,&y))
		{
			top++;
			p[top].x = x;
			p[top].y = y;
			for(int i=0; i <= top; i++)
			{
				if(i+1 < top)
					SDL_RenderDrawLine(renderer, p[i].x, p[i].y, p[i+1].x, p[i+1].y);
			}

			if(top >= 1024) top = -1;
		}
		else
			top = -1;

		SDL_RenderPresent(renderer);


    } // end while

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
