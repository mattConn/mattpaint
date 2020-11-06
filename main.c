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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect r;
	r.w = 3;
	r.h = 3;

	int x,y;

	Uint8 *keystate;

	bool running = true;
	bool clear = false;
    while (running)
	{
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		if(clear)
		{
			SDL_RenderClear(renderer);
			clear = false;
		}
    	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

		if(SDL_PollEvent(&event) )
		{
			if(event.type == SDL_QUIT)
				running = false;

			// clear canvas
			if(keystate[SDL_SCANCODE_BACKSPACE])
				clear = true;

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

		SDL_Rect r1,r2;

		if(SDL_BUTTON(SDL_BUTTON_LEFT) && SDL_GetMouseState(&x,&y))
		{
			r.x = x;
			r.y = y;
			SDL_RenderFillRect(renderer,&r);
		}


		SDL_RenderPresent(renderer);


    } // end while

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
