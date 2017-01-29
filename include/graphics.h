#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <player.h>

#define BLOCKSIZE 20

#define GRID_CONSTRUCT(type, name, y, x)		\
	typedef struct{								\
		int max_y;								\
		int max_x;								\
		block *blocks[y][x];					\
	} type;										\
	type *name = malloc(sizeof(type));			\
	(name)->max_y = y;							\
	(name)->max_x = x;							\

#define GRID_INIT(name)										\
	for(int y = 0; y < (name)->max_y; ++y){					\
		for(int x = 0; x < (name)->max_x; ++x){						\
			(name)->blocks[y][x] = malloc(sizeof(block));	\
			(name)->blocks[y][x]->bitmap_id = 0;			\
			(name)->blocks[y][x]->hidden = 0;				\
			(name)->blocks[y][x]->texture = NULL;			\
			SDL_Rect *rect = malloc(sizeof(SDL_Rect));		\
			rect->x = BLOCKSIZE * x;						\
			rect->y = BLOCKSIZE * y;						\
			rect->w = BLOCKSIZE;							\
			rect->h = BLOCKSIZE;							\
			(name)->blocks[y][x]->rect = rect;				\
		}													\
	}														\


#define GRID_RENDER(name, renderer)							\
	for(int y = 0; y < (name)->max_y; ++y){					\
		for(int x = 0; x < (name)->max_x; ++x){				\
			render_block(renderer, (name)->blocks[y][x]);	\
		}													\
	}														\

#define GRID_COPY(dst, src)												\
	for(int y = 0; y < (dst)->max_y; ++y){								\
		for(int x = 0; x < (dst)->max_x; ++x){							\
			BLOCK(dst, y, x)->texture = BLOCK(src, y, x)->texture;		\
			BLOCK(dst, y, x)->bitmap_id = BLOCK(src, y, x)->bitmap_id;	\
		}																\
	}																	\

#define BLOCK(name, y, x) (name)->blocks[y][x]	\

#define GRID_UPDATE(name, renderer, char_container)			\
	for(int i = 0; i < (char_container)->size; ++i){		\
		BLOCK(name, (char_container)->chars[i]->y,			\
			  (char_container)->chars[i]->x)->bitmap_id =	\
			(char_container)->chars[i]->bitmap_id;			\
	}														\


SDL_Rect **phoebus;


typedef struct{
	int bitmap_id;
	int hidden;
	char name[50];
	SDL_Texture *texture;
	SDL_Rect *rect;
} block;

typedef struct{
	int capacity;
	int size;
	character **chars;
} character_container;


int render_block(SDL_Renderer *renderer, block *b);

void block_set_bitmap_id(block *b, int id);
void block_set_hidden(block *b, int bool);
void block_set_name(block *b, char *name);
void block_set_texture(block *b, SDL_Texture *texture);
void block_set_rect(block *b, SDL_Rect *rect);

void establish_bitmaps(SDL_Renderer *renderer);

character_container* establish_character_container();
void character_container_append(character_container *container, character *ch);

#endif
