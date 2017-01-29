#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

void cmd_start(pthread_t *thread, player *p);
void cmd_stop();

void cmd_main_thread_funct(void *args);




#endif
