#include <player.h>

player* establish_player(char *name)
{
	player *p = malloc(sizeof(player));
	p->paused = 0;
	p->focus = 0;
	p->chars = malloc(sizeof(character*)*4);
	for(int i = 0; i < 4; ++i)
		p->chars[i] = NULL;

	return p;
	
}


void player_set_name(player *p, char *name)
{
	p->name = name;
}


void player_set_paused(player *p, int bool)
{
	p->paused = bool;
}


void player_set_focus(player *p, int focus)
{
	p->focus = focus;
}





int player_create_character(player *p, int x, int y, int bitmap_id)
{
	int char_index;
	int char_array_full = 1;
	for(char_index = 0; char_index < 4; ++char_index){
		if(p->chars[char_index] == NULL){
			char_array_full = 0;
			break;
		}
	}
	if(char_array_full)
		return -1;
	p->chars[char_index] = malloc(sizeof(character));

	p->chars[char_index]->x = x;
	p->chars[char_index]->y = y;
	p->chars[char_index]->bitmap_id = bitmap_id;

	p->focus = char_index;
	
	return 0;
}


void player_delete_character(player *p, int character_index)
{
	
}


void player_move_character(player *p, char *direction)
{
	if(strcmp(direction,"n") == 0){
		p->chars[p->focus]->y--;
	}
	if(direction == "ne"){
		p->chars[p->focus]->y--;
		p->chars[p->focus]->x++;
		
	}
	if(strcmp(direction, "e") == 0){
		p->chars[p->focus]->x++;		
	}
	if(direction == "se"){
		p->chars[p->focus]->y++;
		p->chars[p->focus]->x++;

	}
	if(strcmp(direction, "s") == 0){
		p->chars[p->focus]->y++;
		
	}
	if(direction == "sw"){
		p->chars[p->focus]->y++;
		p->chars[p->focus]->x--;
		
	}
	if(strcmp(direction, "w") == 0){
		p->chars[p->focus]->x--;
		
	}
	if(direction == "nw"){
		p->chars[p->focus]->y--;
		p->chars[p->focus]->x--;
		
	}
	
}





void player_get_input(player *p, char *string)
{
	printf("> ");
	fgets(string, 255, stdin);
	
}


