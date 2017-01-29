#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <graphics.h>
#include <player.h>

#define TRUE  1
#define FALSE 0


int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *window = SDL_CreateWindow("test", 0, 0, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
												SDL_RENDERER_ACCELERATED |
												SDL_RENDERER_PRESENTVSYNC );

	/* Establish game core. */

	SDL_Surface *surface = IMG_Load("textures/Phoebus_16x16.png");
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	establish_bitmaps(renderer);

	character_container *ch_container = establish_character_container();
	
	GRID_CONSTRUCT(Grid, grid, 40, 40);
	GRID_INIT(grid);

	GRID_CONSTRUCT(Map, map, 40, 40);
	GRID_INIT(map);
	
	for(int y = 0; y < map->max_y; ++y){
		for(int x = 0; x < map->max_x; ++x){
			BLOCK(map, y, x)->texture = texture;
			BLOCK(map, y, x)->bitmap_id = 131;
		}
	}

	
	//GRID_COPY(grid, map);
	player *alex = establish_player("alex");
	player_create_character(alex, 0, 0, 1);
	character_container_append(ch_container, alex->chars[0]);


	printf("%i\n", alex->focus);
	
	/* Poll events */
	SDL_Event e;

	int is_running = TRUE;

	while( is_running ){
		
		while( SDL_PollEvent(&e) != 0 ){
			if(e.type == SDL_QUIT){
				is_running = FALSE;
			}

			if(e.type == SDL_KEYDOWN){
				if(e.key.keysym.sym == SDLK_w){					
					player_move_character(alex, "n");
				    
				}
				if(e.key.keysym.sym == SDLK_d){
					player_move_character(alex, "e");

				}
				if(e.key.keysym.sym == SDLK_s){
					player_move_character(alex, "s");
					
				}
				if(e.key.keysym.sym == SDLK_a){
					player_move_character(alex, "w");
					
				} 
				
			}	
		}

		
		
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);
		GRID_COPY(grid, map);
		GRID_UPDATE(grid, renderer, ch_container);
		GRID_RENDER(grid, renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	return 0;
}


