#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H



/* COMMANDS:
 * create object
 * delete object
 * move object
 * 
 */ 

void interpret_command(char *command);

int create_object(char *data);
int delete_object(char *data);
int move_object(char *data);




#endif
