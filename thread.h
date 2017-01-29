#ifndef THREAD_H
#define THREAD_H

#include <player.h>

typedef struct{
	player *p;
	char *input;
} text_input_data;



#ifdef LINUX_BUILD
#include <pthread.h>
typedef struct{
	pthread thread;
} thread_wrap;

#define 









#endif


#ifdef WINDOWS_BUILD
#include <windows.h>
typedef struct{
	HANDLE thread;
} thread_wrap;
#endif






#endif
	
