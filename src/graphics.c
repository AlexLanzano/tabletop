#include <graphics.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <math.h>


int render_block(SDL_Renderer *renderer, block *b)
{
	SDL_RenderCopy(renderer, b->texture, phoebus[b->bitmap_id], b->rect);
}

void block_set_bitmap_id(block *b, int bitmap_id)
{
	b->bitmap_id = bitmap_id;
}


void block_set_hidden(block *b, int bool)
{
	b->hidden = bool;
}


void block_set_name(block *b, char *name)
{
	strncpy(b->name, name, 49);
}


void block_set_texture(block *b, SDL_Texture *texture)
{
	b->texture = texture;
}


void block_set_rect(block *b, SDL_Rect *rect)
{
	b->rect = rect;
}
	
SDL_Rect **phoebus;

void establish_bitmaps(SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load("textures/Phoebus_16x16.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	phoebus = malloc(sizeof(SDL_Rect*) * 256);
	int col = 0;
	int row = 0;
	for(int i = 0; i < 256; ++i){
		phoebus[i] = malloc(sizeof(SDL_Rect));

		if(col == 16){
			col = 0;
			++row;
		}
		
		if(col == 0){
			phoebus[i]->x = 0;
		} else {
			phoebus[i]->x = 16 * col;
		}
		if(row == 0){
			phoebus[i]->y = 0;
		} else {
			phoebus[i]->y = 16 * row;
		}
	   
		phoebus[i]->w = 16;
		phoebus[i]->h = 16;
		++col;

	}	
	
}

