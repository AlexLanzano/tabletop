#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int x, y;
	int bitmap_id;
} character;

typedef struct{
	char *name;
	int paused;
	int focus;
	character **chars;
} player;


player* establish_player(char *name);

void player_set_name(player *p, char *name); 
void player_set_paused(player *p, int bool);
void player_set_focus(player *p, int focus);

int player_create_character(player *p, int x, int y, int bitmap_id);
void player_delete_character(player *p, int character_index);
void player_move_character(player *p, char *direction);

void player_get_input(player *p, char *string);

#endif
