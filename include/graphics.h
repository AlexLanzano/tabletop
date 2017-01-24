#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define BLOCKSIZE 20

#define GRID_CONSTRUCT(type, name, win_size)		\
	int size = win_size/BLOCKSIZE;				\
	typedef struct{								\
		int max_x;								\
		int max_y;								\
		block *blocks[size][size];				\
	} type;										\
	type *name = malloc(sizeof(type));			\

#define GRID_INIT(name, size_x, size_y)						\
	(name)->max_x = size_x;									\
	(name)->max_y = size_y;									\
	for(int y = 0; y < size_y; ++y){						\
		for(int x = 0; x < size_x; ++x){					\
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

#define BLOCK(name, y, x) (name)->blocks[y][x]	\

SDL_Rect **phoebus;

typedef struct{
	int bitmap_id;
	int hidden;
	char name[50];
	SDL_Texture *texture;
	SDL_Rect *rect;
} block;



int render_block(SDL_Renderer *renderer, block *b);

void block_set_bitmap_id(block *b, int id);
void block_set_hidden(block *b, int bool);
void block_set_name(block *b, char *name);
void block_set_texture(block *b, SDL_Texture *texture);
void block_set_rect(block *b, SDL_Rect *rect);


void establish_bitmaps(SDL_Renderer *renderer);



